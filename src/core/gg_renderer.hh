#ifndef GG_RENDERER_HH
#define GG_RENDERER_HH


#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


namespace gg 
{
class Renderer
{
public:

    Renderer(SDL_Window& win);
    ~Renderer();

    void setColor(int r, int g, int b, int a=255);
    void setFont(const std::string& name, int size);
    void setClip(int x, int y, int w, int h);
    void unsetClip();

    void drawRect(int x, int y, int w, int h);
    void drawText(const std::string& txt, int x, int y, int w, int h);
    void fillRect(int x, int y, int w, int h);

    /* clear
    Clears the entire screen to currently selected color. */

    void clear();

    /* render
    Updates the screen with any rendering performed since the previous call.
    Call this to actually display things on screen. */

    void render();

private:

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