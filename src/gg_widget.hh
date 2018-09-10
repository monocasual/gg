
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
class BaseGroup;


class Widget
{
protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* label
	A string of text to display inside, outside or near your widget. */

	const char* m_label;

	/* resizeW, resizeH
	If true, resize the widget horizontally or vertically when the window 
	changes. */

	bool m_resizeW, m_resizeH;

	/* parent
	Widgets belong to a group, be it a Window or a Group. */

	BaseGroup* m_parent;

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

	/* xywh()
	Returns coordinates. */
	
	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;
	int getXW() const;
	int getYH() const;

	/* resizableW/H()
	Returns whether widget is resizable. */

	bool isResizableW() const;
	bool isResizableH() const;

	/* resize()
	Sets new size. */

	virtual void resize(int w, int h);

	void setResizable(bool rw, bool rh);

	/* setParent
	Add a pointer to the parent widget. Every window must call this function when 
	a new widget is added. */

	void setParent(BaseGroup* g);
};
} // g::


#endif
