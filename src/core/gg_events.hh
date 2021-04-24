#ifndef GG_EVENTS_HH
#define GG_EVENTS_HH

#include "deps/geompp/src/point.hpp"
#include "deps/geompp/src/rect.hpp"
#include "gg.hh"

namespace gg
{
class Element;

struct MouseEvent
{
	MouseEvent(int x, int y);

	bool isOver(geompp::Rect<int> r) const;

	geompp::Point<int> position;
};

struct KeyEvent
{
	enum class Type
	{
		TEXT,
		BACKSPACE
	};

	Type        type;
	const char* ch;
};

MouseEvent makeMouseEvent();
KeyEvent   makeTextKeyEvent(const SDL_Event& e);
KeyEvent   makeFuncKeyEvent(KeyEvent::Type t);
} // namespace gg

#endif