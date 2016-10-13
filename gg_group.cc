#include <SDL2/SDL.h>
#include "gg_group.hh"
#include "gg_window.hh"


ggGroup::ggGroup (int x, int y, int w, int h)
	: ggBaseGroup(), ggWidget(x, y, w, h)
{
}


/* ------------------------------------------------------------------ */


int ggGroup::add(ggWidget *w)
{
	if (ggBaseGroup::add(w)) {
		w->addWindow(window);
		return 1;
	}
	return 0;
}


/* ------------------------------------------------------------------ */


void ggGroup::draw()
{
	SDL_SetRenderDrawColor(window->ren, 255, 255, 255, 255);
	SDL_Rect rect = {x(), y(), w(), h()};
	SDL_RenderDrawRect(window->ren, &rect);
	for (int i=0; i<size; i++)
		stack[i]->draw();
}


/* ------------------------------------------------------------------ */


void ggGroup::handle(SDL_Event &e)
{
	for (int i=0; i<size; i++)
		stack[i]->handle(e);
}
