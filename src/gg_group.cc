#include <SDL2/SDL.h>
#include "gg_group.hh"
#include "gg_window.hh"


namespace gg
{
Group::Group (int x, int y, int w, int h)
	: BaseGroup(), 
	  Widget   (x, y, w, h)
{
}


/* -------------------------------------------------------------------------- */


int Group::add(Widget* w)
{
	if (BaseGroup::add(w)) {
		w->addWindow(m_window);
		return 1;
	}
	return 0;
}


/* -------------------------------------------------------------------------- */


void Group::draw()
{
	SDL_SetRenderDrawColor(m_window->ren, 255, 255, 255, 255);
	SDL_Rect rect = {getX(), getY(), getW(), getH()};
	SDL_RenderDrawRect(m_window->ren, &rect);
	for (Widget* w : m_stack)
		w->draw();
}


/* -------------------------------------------------------------------------- */


void Group::handle(const SDL_Event& e)
{
	for (Widget* w : m_stack)
		w->handle(e);
}

} // gg::