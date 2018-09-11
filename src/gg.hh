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

/* loadFont()
Loads a font for drawing text. */

int loadFont(const char* f, int size);

/* quit()
Sends a quit event to the main loop. Call this whenever you want to quit the
app from outside the main loop (e.g. a button callback). */

void quit();

/* getFontInfo()
Returns information on the current loaded font. */

FontInfo& getFontInfo();

void drawFont(SDL_Renderer* ren, SDL_Rect rc, const char* t);

void freeFont();

} // gg::