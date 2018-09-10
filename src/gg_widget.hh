
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
class Element;


class Widget
{
protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* parent
	Widgets belong to a group, be it a Window or a Group. */

	Element* m_parent;

	Widget();

	void redraw();

public:

	virtual ~Widget();

	/* draw() [pure virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw(SDL_Renderer* ren) = 0;

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

	/* setParent
	Add a pointer to the parent widget. Every window must call this function when 
	a new widget is added. */

	void setParent(Element* g);

	void setBounds(int x, int y, int w, int h);
};
} // g::


#endif
