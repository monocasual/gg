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
} // gg::