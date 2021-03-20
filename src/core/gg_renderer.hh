#ifndef GG_RENDERER_HH
#define GG_RENDERER_HH


#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gg.hh"


namespace gg 
{
struct Color
{
    int r = 0;
    int g = 0; 
    int b = 0;
    int a = 255;
};


/* -------------------------------------------------------------------------- */


class Renderer
{
public:

    enum class TextAlign { LEFT, CENTER, RIGHT };

    Renderer(SDL_Window& win);
    ~Renderer();

    Rect getTextBounds(const std::string& txt) const;

    void setColor(Color c);
    void setFont(const std::string& name, int size);
    void setClip(int x, int y, int w, int h);
    void setClip(Rect r);
    void unsetClip();

    void drawRect(int x, int y, int w, int h);
    void drawRect(Rect r);
    void drawText(const std::string& txt, int x, int y, int w, int h, TextAlign t=TextAlign::CENTER);
    void drawText(const std::string& txt, Rect r, TextAlign t=TextAlign::CENTER);
    void fillRect(int x, int y, int w, int h);
    void fillRect(Rect r);

    void drawLine(int x1, int y1, int x2, int y2) const;

    /* clear
    Clears the entire screen to currently selected color. */

    void clear();

    /* render
    Updates the screen with any rendering performed since the previous call.
    Call this to actually display things on screen. */

    void render();

private:

    Color getCurrentColor() const;

    /* Info on SDL renderer:
    http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer */

    SDL_Renderer* m_ren;

    /* font
    Pointer to a TTF resource. 
    TODO - I don't think each renderer needs a TTF_Font pointer. One per
    app instance should be enough. To be investigated... */

    TTF_Font* m_font; 
};
} // gg::


#endif