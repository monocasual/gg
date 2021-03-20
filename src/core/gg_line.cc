#include "gg_line.hh"


namespace gg 
{
Line::Line() : Line(0, 0, 0, 0)
{
}


/* -------------------------------------------------------------------------- */


Line::Line(int x1, int y1, int x2, int y2)
: x1(x1), y1(y1), x2(x2), y2(y2)
{
}


Line::Line(int x, int y1, int y2)
: x1(x), y1(y1), x2(x), y2(y2)
{
}


/* -------------------------------------------------------------------------- */


Line Line::withShiftedX(int x) const
{
    Line l = *this;
    l.shiftX(x);
    return l;
}


/* -------------------------------------------------------------------------- */


void Line::shiftX(int x)
{
    x1 = x;
    x2 = x;
}

} // gg::