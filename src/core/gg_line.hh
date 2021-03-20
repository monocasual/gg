#ifndef GG_LINE_HH
#define GG_LINE_HH


namespace gg 
{
class Line
{
public:

    Line();
    Line(int x1, int y1, int x2, int y2);

    /* Line (2) - vertical. */

    Line(int x, int y1, int y2);

    Line withShiftedX(int x) const;

    void shiftX(int x);

    int x1, y1, x2, y2;

private:
};
} // gg::


#endif