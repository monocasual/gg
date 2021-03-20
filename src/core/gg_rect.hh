#ifndef GG_RECT_HH
#define GG_RECT_HH


#include "core/gg_line.hh"

namespace gg 
{
class Rect
{
public:

    Rect();
    Rect(int x, int y, int w, int h);

    Line getHeightAsLine() const;

    int x, y, w, h, xw, yh;

private:
};
} // gg::


#endif