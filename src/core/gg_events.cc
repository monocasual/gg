#include "gg_events.hh"
#include "gg_element.hh"
#include <SDL2/SDL.h>

namespace gg
{
MouseEvent::MouseEvent(int x, int y)
: position(x, y)
{
}

/* -------------------------------------------------------------------------- */

bool MouseEvent::isOver(geompp::Rect<int> r) const
{
	return r.contains(position);
}

/* -------------------------------------------------------------------------- */

MouseEvent makeMouseEvent()
{
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	return {mx, my};
}

/* -------------------------------------------------------------------------- */

KeyEvent makeTextKeyEvent(const SDL_Event& e)
{
	return {KeyEvent::Type::TEXT, e.text.text};
}

KeyEvent makeFuncKeyEvent(KeyEvent::Type t)
{
	return {t, nullptr};
}
} // namespace gg
