#ifndef GG_HH
#define GG_HH


#include <SDL2/SDL.h>


namespace gg 
{
class Window;

/* init()
 * */

int init();

/* addWindow()
 * */

void addWindow(Window* w);


void removeWindow(Window* w);

/* run()
 * */

void run();

/* quit()
Sends a quit event to the main loop. Call this whenever you want to quit the
app from outside the main loop (e.g. a button callback). */

void quit();
} // gg::


#endif