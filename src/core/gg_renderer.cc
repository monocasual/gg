#include <cassert>
#include "gg_renderer.hh"


namespace gg 
{
Renderer::Renderer(SDL_Window& win)
{
	m_ren = SDL_CreateRenderer(&win, -1, SDL_RENDERER_ACCELERATED);
	// TODO throw on failure

	m_font = TTF_OpenFontIndex("../src/fonts/pixelmix.ttf", 12, 0);
	/*
	if (m_font == nullptr)
	{
		// TODO throw on failure
		printf("[ggWidget::setFont] unable to load font: %s\n", TTF_GetError());
	}*/
}


/* -------------------------------------------------------------------------- */


void Renderer::setColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(m_ren, r, g, b, a); 
}


/* -------------------------------------------------------------------------- */


void Renderer::setFont(const char* name, int size)
{
	// TODO
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


void Renderer::drawText(const char* txt, int x, int y, int w, int h)
{
	SDL_Rect  rect       = { x, y, w, h };
	SDL_Color color      = { 255, 255, 255 };
	SDL_Surface* surf    = TTF_RenderText_Solid(m_font, txt, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_ren, surf);
	SDL_FreeSurface(surf);

	int tw, th;
	TTF_SizeText(m_font, txt, &tw, &th);

	if (tw > rect.w)
		printf("[drawFont] warning: string overflow (%d px)\n", tw - rect.w);

	rect.x = rect.x + (rect.w / 2) - (tw / 2);
	rect.y = rect.y + (rect.h / 2) - (th / 2);
	rect.w = tw;
	rect.h = th;

	SDL_RenderCopy(m_ren, texture, nullptr, &rect);    
}


/* -------------------------------------------------------------------------- */


Renderer::~Renderer()
{
	SDL_DestroyRenderer(m_ren);
	TTF_CloseFont(m_font);
}

} // gg::