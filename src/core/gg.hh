#ifndef GG_HH
#define GG_HH

#include <memory>

namespace gg
{
class Window;
struct Style;

/* init()
 * */

int init();

/* addWindow()
 * */

void addWindow(Window* w);

void removeWindow(Window* w);

const Style& getStyle();
void         setStyle(std::unique_ptr<Style> s);

/* run()
 * */

void run();

/* quit()
Sends a quit event to the main loop. Call this whenever you want to quit the
app from outside the main loop (e.g. a button callback). */

void quit();
} // namespace gg

#endif