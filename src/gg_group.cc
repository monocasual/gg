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


void Group::draw()
{
	for (Widget* w : m_widgets)
		w->draw();
}


/* -------------------------------------------------------------------------- */


void Group::handle(const SDL_Event& e)
{
	for (Widget* w : m_widgets)
		w->handle(e);
}

} // gg::