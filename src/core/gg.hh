#ifndef GG_HH
#define GG_HH


#include <SDL2/SDL.h>


namespace gg 
{
class Window;

/* init()
 * */

int init();

/* add()
 * */

void add(Window* w);

/* run()
 * */

int run();

/* quit()
Sends a quit event to the main loop. Call this whenever you want to quit the
app from outside the main loop (e.g. a button callback). */

void quit();
} // gg::


#endif