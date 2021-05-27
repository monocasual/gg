#include "gg_renderer.hh"
#include "deps/mcl-utils/src/log.hpp"
#include "gg_const.hh"
#include <cassert>
#include <new>

namespace gg
{
Renderer::Renderer(SDL_Window& win)
: m_ren(nullptr)
, m_font(nullptr)
{
	if (TTF_Init() == -1)
	{
		ML_DEBUG("TTF_Init: " << TTF_GetError());
		throw std::bad_alloc();
	}

	m_ren = SDL_CreateRenderer(&win, -1, SDL_RENDERER_ACCELERATED);
	if (m_ren == nullptr)
	{
		ML_DEBUG("SDL_CreateRenderer: " << SDL_GetError());
		throw std::bad_alloc();
	}

	setFont(GG_DEFAULT_FONT_PATH, 16);
}

/* -------------------------------------------------------------------------- */

Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_ren);
	TTF_CloseFont(m_font);
	TTF_Quit();
}

/* -------------------------------------------------------------------------- */

geompp::Rect<int> Renderer::getTextBounds(const tiny_utf8::string& txt) const
{
	int tw, th;
	TTF_SizeUTF8(m_font, txt.c_str(), &tw, &th);
	return {0, 0, tw, th};
}

/* -------------------------------------------------------------------------- */

void Renderer::setColor(Color c)
{
	SDL_SetRenderDrawColor(m_ren, c.r, c.g, c.b, c.a);
}

/* -------------------------------------------------------------------------- */

void Renderer::setFont(const std::string& path, int size)
{
	if (m_font != nullptr)
		TTF_CloseFont(m_font);
	m_font = TTF_OpenFont(path.c_str(), size);
	if (m_font == nullptr)
	{
		ML_DEBUG("TTF_OpenFont: " << TTF_GetError());
		throw std::bad_alloc();
	}
}

/* -------------------------------------------------------------------------- */

void Renderer::setClip(int x, int y, int w, int h)
{
	SDL_Rect r{x, y, w, h};
	SDL_RenderSetClipRect(m_ren, &r);
}

void Renderer::setClip(geompp::Rect<int> r)
{
	setClip(r.x, r.y, r.w, r.h);
}

void Renderer::unsetClip()
{
	SDL_RenderSetClipRect(m_ren, nullptr);
}

/* -------------------------------------------------------------------------- */

void Renderer::clear()
{
	SDL_RenderClear(m_ren);
}

void Renderer::render()
{
	SDL_RenderPresent(m_ren);
}

/* -------------------------------------------------------------------------- */

void Renderer::drawRect(int x, int y, int w, int h)
{
	SDL_Rect r{x, y, w, h};
	SDL_RenderDrawRect(m_ren, &r);
}

void Renderer::drawRect(geompp::Rect<int> r)
{
	drawRect(r.x, r.y, r.w, r.h);
}

void Renderer::fillRect(int x, int y, int w, int h)
{
	SDL_Rect r{x, y, w, h};
	SDL_RenderFillRect(m_ren, &r);
}

void Renderer::fillRect(geompp::Rect<int> r)
{
	fillRect(r.x, r.y, r.w, r.h);
}

/* -------------------------------------------------------------------------- */

void Renderer::drawText(const tiny_utf8::string& txt, int x, int y, int w, int h,
    TextAlign align)
{
	SDL_Color fgcolor;
	SDL_GetRenderDrawColor(m_ren, &fgcolor.r, &fgcolor.g, &fgcolor.b, &fgcolor.a);

	/* Solid, shaded or blended font rendering: 
	https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf_42.html */

	SDL_Surface* surf    = TTF_RenderUTF8_Blended(m_font, txt.c_str(), fgcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_ren, surf);
	SDL_FreeSurface(surf);

	geompp::Rect<int> txtBounds = getTextBounds(txt);

	if (txtBounds.w > w)
		ML_DEBUG("String overflow (" << txtBounds.w - w << " px)");

	SDL_Rect rect = {x, y, w, h};
	rect.y        = rect.y + (rect.h / 2) - (txtBounds.h / 2); // h-centered
	rect.w        = txtBounds.w;
	rect.h        = txtBounds.h;

	if (align == TextAlign::CENTER)
		rect.x = rect.x + (w / 2) - (txtBounds.w / 2);
	else if (align == TextAlign::RIGHT)
		rect.x = rect.x + (w - txtBounds.w);

	SDL_RenderCopy(m_ren, texture, nullptr, &rect);
	SDL_DestroyTexture(texture);
}

void Renderer::drawText(const tiny_utf8::string& txt, geompp::Rect<int> r, TextAlign t)
{
	drawText(txt, r.x, r.y, r.w, r.h, t);
}

/* -------------------------------------------------------------------------- */

void Renderer::drawLine(int x1, int y1, int x2, int y2) const
{
	SDL_RenderDrawLine(m_ren, x1, y1, x2, y2);
}

void Renderer::drawLine(geompp::Line<int> l) const
{
	drawLine(l.x1, l.y1, l.x2, l.y2);
}
} // namespace gg