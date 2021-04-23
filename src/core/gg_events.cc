#include "gg_events.hh"
#include "gg_element.hh"
#include <SDL2/SDL.h>

namespace gg
{
bool MouseEvent::isOver(geompp::Rect<int> r) const
{
	return x < r.xw && x > r.x && y < r.yh && y > r.y;
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
