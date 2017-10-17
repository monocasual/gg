
/* Widget --------------------------------------------------------------------
 *
 * A generic widget. Normally you don't want to use a Widget directly,
 * but extend it with your own widget.
 *
 * -------------------------------------------------------------------------- */


#ifndef GG_WIDGET_HH
#define GG_WIDGET_HH


#include <SDL2/SDL.h>


namespace gg 
{
class Window;

class Widget
{
protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h, m_xw, m_yh;

	/* label
	A string of text to display inside, outside or near your widget. */

	const char* m_label;

	/* resizeW, resizeH
	If true, resize the widget horizontally or vertically when the window 
	changes. */

	bool m_resizeW, m_resizeH;

	/* window
	Widgets belong to a window, so this pointer points to a parent window. */

	Window* m_window;

	/* callback_t
	Function pointer called when the entity has to do something. Typedef for ease 
	of use. */

	typedef void (callback_t)(void*);
	callback_t* m_callback;
	void* m_callbackData;

	Widget(int x, int y, int w, int h, const char* l=nullptr);

public:

	virtual ~Widget();

	/* draw() [pure virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw() = 0;

	/* handle() [pure virtual]
	Handles events such as click, keypress, show-hide and so on. */

	virtual void handle(const SDL_Event& e) = 0;

	/* resize()
	Sets new size. */

	virtual void resize(int w, int h);

	/* xywh()
	Returns coordinates. */
	
	int x() const;
	int y() const;
	int w() const;
	int h() const;
	int xw() const;
	int yh() const;

	/* resizableW/H()
	Returns whether widget is resizable. */

	bool resizableW() const;
	bool resizableH() const;
	void resizable(bool rw, bool rh);

	/* addParent
	Add a pointer to the parent widget. Every window must call this function when 
	a new widget is added. */

	void addWindow(Window* w);

	/* setCallback()
	Attaches a m_callback to this widget. */

	void addCallback(callback_t* cb, void* cbData);

	/* doCallback()
	Runs the m_callback, if set. */

	void doCallback() const;
};
} // g::


#endif
