#include <new>
#include <cassert>
#include "gg_const.hh"
#include "gg_renderer.hh"


namespace gg 
{
Renderer::Renderer(SDL_Window& win)
{
	if (TTF_Init() == -1)
	{
		GG_DEBUG("TTF_Init: " << TTF_GetError());
		throw std::bad_alloc();
	}

	m_ren = SDL_CreateRenderer(&win, -1, SDL_RENDERER_ACCELERATED);
	if (m_ren == nullptr)
	{
		GG_DEBUG("SDL_CreateRenderer: " << SDL_GetError());
		throw std::bad_alloc();
	}

	m_font = TTF_OpenFont("src/fonts/alterebro.ttf", 32);
	if (m_font == nullptr)
	{
		GG_DEBUG("TTF_OpenFont: " << TTF_GetError());
		throw std::bad_alloc();
	}
}


/* -------------------------------------------------------------------------- */


Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_ren);
	TTF_CloseFont(m_font);
	TTF_Quit();
}


/* -------------------------------------------------------------------------- */


Rect Renderer::getTextBounds(const std::string& txt) const
{
	int tw, th;
	TTF_SizeText(m_font, txt.c_str(), &tw, &th);
	return {0, 0, tw, th};	
}


/* -------------------------------------------------------------------------- */


void Renderer::setColor(Color c)
{
	SDL_SetRenderDrawColor(m_ren, c.r, c.g, c.b, c.a); 
}


/* -------------------------------------------------------------------------- */


void Renderer::setFont(const std::string& name, int size)
{
	// TODO
}


/* -------------------------------------------------------------------------- */


void Renderer::setClip(int x, int y, int w, int h)
{
	SDL_Rect r { x, y, w, h };
	SDL_RenderSetClipRect(m_ren, &r);
}


void Renderer::setClip(Rect r)
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
	SDL_Rect r { x, y, w, h };
	SDL_RenderDrawRect(m_ren, &r);
}


void Renderer::drawRect(Rect r)
{
	drawRect(r.x, r.y, r.w, r.h);
}


void Renderer::fillRect(int x, int y, int w, int h)
{
	SDL_Rect r { x, y, w, h };
	SDL_RenderFillRect(m_ren, &r);
}


void Renderer::fillRect(Rect r)
{
	fillRect(r.x, r.y, r.w, r.h);
}


/* -------------------------------------------------------------------------- */


void Renderer::drawText(const std::string& txt, int x, int y, int w, int h, 
	TextAlign align)
{
	SDL_Color fgcolor = { 255, 255, 255 };

	SDL_Surface* surf    = TTF_RenderUTF8_Solid(m_font, txt.c_str(), fgcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_ren, surf);
	SDL_FreeSurface(surf);

	Rect txtBounds = getTextBounds(txt);

	if (txtBounds.w > w)
		GG_DEBUG("String overflow (" << txtBounds.w - w << " px)");

	SDL_Rect rect = { x, y, w, h };
	rect.y = rect.y + (rect.h / 2) - (txtBounds.h / 2); // h-centered
	rect.w = txtBounds.w;
	rect.h = txtBounds.h;

	if (align == TextAlign::CENTER)
		rect.x = rect.x + (w / 2) - (txtBounds.w / 2);
	else
	if (align == TextAlign::RIGHT)
		rect.x = rect.x + (w - txtBounds.w);

	SDL_RenderCopy(m_ren, texture, nullptr, &rect);
	SDL_DestroyTexture(texture);
}


void Renderer::drawText(const std::string& txt, Rect r, TextAlign t)
{
	drawText(txt, r.x, r.y, r.w, r.h, t);
}


/* -------------------------------------------------------------------------- */


void Renderer::drawLine(int x1, int y1, int x2, int y2) const
{
	SDL_RenderDrawLine(m_ren, x1, y1, x2, y2);
}
} // gg::