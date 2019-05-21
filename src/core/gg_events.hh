#ifndef GG_EVENTS_HH
#define GG_EVENTS_HH


namespace gg 
{
class Element;
struct MouseEvent
{
    int x;
    int y;

    bool isOver(const Element& e) const;
};

MouseEvent makeMouseEvent();
}; // gg::


#endif