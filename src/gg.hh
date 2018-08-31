#include <SDL2/SDL.h>


namespace gg 
{
class Window;

struct FontInfo
{
	int height;
};


/* init()
 * */

int init();

/* add()
 * */

void add(Window* w);

/* run()
 * */

int run();

/* end()
 * */

void end();

/* loadFont()
Loads a font for drawing text. */

int loadFont(const char* f, int size);

FontInfo& getFontInfo();

void drawFont(SDL_Renderer* ren, SDL_Rect rc, const char* t);

void freeFont();

} // gg::