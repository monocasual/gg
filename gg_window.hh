#ifndef __GG_WINDOW_HH__
#define __GG_WINDOW_HH__


#include <SDL2/SDL.h>
#include "gg_baseGroup.hh"
#include "gg_widget.hh"


class ggWindow : public ggBaseGroup
{
protected:

	/* xywh
	 * main coordinates. */

	int _x, _y, _w, _h;

	/* win
	 * pointer to a SDL_Window structure. */

	SDL_Window *win;

	/* preW, preH
	 * previous width and height for calculating increments. */

	int preW, preH;

public:

	/* id
	 * unique id of this window. */

	int id;

	/* SLD_Renderer
	 * each window contains a public renderer. Any widget must refer to
	 * this pointer in order to draw something. Also they can call
	 * other ggWindow's function to refresh screen and such. Info on
	 * SDL renderer:
	 * http://stackoverflow.com/questions/21007329/what-is-a-sdl-renderer */

	SDL_Renderer *ren;

	/* damaged
	 * a damaged window must be redrawn. Each subwidget must set this flag
	 * to true when it needs to update the screen. */

	bool damaged;

	ggWindow (const char *t, int x, int y, int w, int h);
	~ggWindow();

	/* xywh()
	 * set and return coordinates. */

	inline int x()  { return _x; }
	inline int y()  { return _y; }
	inline int w()  { return _w; }
	inline int h()  { return _h; }
	inline void x(int x) { _x = x; }
	inline void y(int y) { _y = y; }

	void resize(int w, int h);

	/* add()
	 * add a new widget to this window. */

	int add(ggWidget *w);

	/* show()
	 * show the window on screen. */

	void show();

	/* clear()
	 * delete all widget from screen and cover it with the regular
	 * background. */

	void clear();

	/* drawChildren()
	 * call draw() for each child in the group. */

	void drawChildren();

	/* render()
	 * update the screen after the children have been drawn. */

	void render();

	void handle(SDL_Event &e);
};


#endif
