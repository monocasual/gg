#include <new>
#include <cassert>
#include "gg_renderer.hh"


namespace gg 
{
Renderer::Renderer(SDL_Window& win)
{
	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		throw std::bad_alloc();
	}

	m_ren = SDL_CreateRenderer(&win, -1, SDL_RENDERER_ACCELERATED);
	if (m_ren == nullptr)
	{
		printf("SDL_CreateRenderer: %s\n", SDL_GetError());
		throw std::bad_alloc();
	}

	m_font = TTF_OpenFont("../src/fonts/alterebro.ttf", 32);
	if (m_font == nullptr)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
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


void Renderer::fillRect(int x, int y, int w, int h)
{
	SDL_Rect r { x, y, w, h };
	SDL_RenderFillRect(m_ren, &r);
}


/* -------------------------------------------------------------------------- */


void Renderer::drawText(const std::string& txt, int x, int y, int w, int h)
{
	SDL_Color fgcolor = { 255, 255, 255 };

	SDL_Surface* surf    = TTF_RenderUTF8_Solid(m_font, txt.c_str(), fgcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_ren, surf);
	SDL_FreeSurface(surf);

	int tw, th;
	TTF_SizeText(m_font, txt.c_str(), &tw, &th);

	if (tw > w)
		printf("[Renderer] warning: string overflow (%d px)\n", tw - w);

	SDL_Rect rect = { x, y, w, h };
	rect.x = rect.x + (rect.w / 2) - (tw / 2);
	rect.y = rect.y + (rect.h / 2) - (th / 2);
	rect.w = tw;
	rect.h = th;

	SDL_RenderCopy(m_ren, texture, nullptr, &rect);
	SDL_DestroyTexture(texture);
}

} // gg::