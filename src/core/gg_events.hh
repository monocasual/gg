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

    bool isOver(Rect r) const;
};

MouseEvent makeMouseEvent();
}; // gg::


#endif