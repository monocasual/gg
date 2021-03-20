#ifndef GG_RECT_HH
#define GG_RECT_HH


namespace gg 
{
class Rect
{
public:

    Rect();
    Rect(int x, int y, int w, int h);

    int x, y, w, h, xw, yh;

private:
};
} // gg::


#endif