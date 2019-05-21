#include <SDL2/SDL.h>
#include "gg_element.hh"
#include "gg_events.hh"


namespace gg 
{
bool MouseEvent::isOver(const Element& e) const
{
    return x < e.getXW() && x > e.getX() && y < e.getYH() && y > e.getY();
}


/* -------------------------------------------------------------------------- */



MouseEvent makeMouseEvent()
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    return { mx, my };
}
}; // gg::

