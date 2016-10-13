
/* ggWidget ------------------------------------------------------------
 *
 * A generic widget. Normally you don't want to use a ggWidget directly,
 * but extend it with your own widget.
 *
 * ------------------------------------------------------------------ */


#ifndef __GG_WIDGET_HH__
#define __GG_WIDGET_HH__


#include <SDL2/SDL.h>


class ggWidget
{
protected:

	/* xywh
	 * main coordinates. */

	int _x, _y, _w, _h, _xw, _yh;

	/* label
	 * a string of text to display inside, outside or near your widget. */

	const char *label;

	/* resizeW, resizeH
	 * if true, resize the widget horizontally or vertically when the
	 * window changes. */

	bool resizeW, resizeH;

	/* window
	 * widgets belong to a window, so this pointer points to a parent
	 * window. */

	class ggWindow *window;

	/* callback
	 * function pointer called when the entity has to do something.
	 * Typedef for ease of use. */

	typedef void (ggCallback)(void*);
	ggCallback *callback;
	void       *callbackData;

public:

	ggWidget(int x, int y, int w, int h, const char *l=NULL);
	virtual ~ggWidget();

	/* xywh()
	 * return coordinates. */

	inline int x()  { return _x; }
	inline int y()  { return _y; }
	inline int w()  { return _w; }
	inline int h()  { return _h; }
	inline int xw() { return _xw; }
	inline int yh() { return _yh; }

	/* resize()
	 * set new size. */

	virtual void resize(int w, int h);

	/* resizableW/H()
	 * return if widget is resizable. */

	inline bool resizableW() { return resizeW; }
	inline bool resizableH() { return resizeH; }
	inline void resizable(bool rw, bool rh) { resizeW = rw; resizeH = rh; }

	/* addParent
	 * add a pointer to the parent widget. Every window must call
	 * this function when a new widget is added. */

	inline void addWindow(class ggWindow *w) { window = w; }

	/* setCallback()
	 * attach a callback to this widget. */

	void addCallback(ggCallback *cb, void *cbData);

	/* doCallback()
	 * run the callback, if set. */

	void doCallback();

	/* draw() [pure virtual]
	 * Drawing routines. This method draws the initial graphical state of
	 * each widget. */

	virtual void draw() = 0;

	/* handle() [pure virtual]
	 * handle events such as click, keypress, show-hide and so on. */

	virtual void handle(SDL_Event &e) = 0;
};


#endif
