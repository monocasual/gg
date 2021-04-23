#ifndef GG_EVENTS_HH
#define GG_EVENTS_HH


#include "gg.hh"


namespace gg 
{
class Element;

struct MouseEvent
{
    int x;
    int y;

    bool isOver(geompp::Rect<int> r) const;
};

struct KeyEvent
{
    enum class Type 
    {
        TEXT, BACKSPACE 
    };

    Type        type;
    const char* ch;
};

MouseEvent makeMouseEvent();
KeyEvent makeTextKeyEvent(const SDL_Event& e);
KeyEvent makeFuncKeyEvent(KeyEvent::Type t);
} // gg::


#endif