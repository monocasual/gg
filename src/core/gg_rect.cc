#include "gg_rect.hh"


namespace gg 
{
Rect::Rect() : Rect(0, 0, 0, 0)
{
}


/* -------------------------------------------------------------------------- */


Rect::Rect(int x, int y, int w, int h)
: x(x), y(y), w(w), h(h), xw(x + w), yh(y + h)
{
}


/* -------------------------------------------------------------------------- */


Line Rect::getHeightAsLine() const
{
    return Line(0, y, yh);
}
} // gg::