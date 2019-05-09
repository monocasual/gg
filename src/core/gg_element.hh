/* Element ---------------------------------------------------------------------

A generic base for everything.

----------------------------------------------------------------------------- */


#ifndef GG_ELEMENT_HH
#define GG_ELEMENT_HH


#include <vector>
#include <SDL2/SDL.h>


namespace gg 
{
class Window;
class Renderer;
class Element
{
public:

	virtual ~Element();

	/* handle() [virtual]
	Fired on events such as click, keypress, window show-hide and so on. */

	virtual void handle(const SDL_Event& e) {};

	/* resized() [virtuals]
	Fired when the element position and size change. */

	virtual void resized() {};

	/* draw() [virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw(Renderer& ren) {};

	/* add()
	Adds a child widget to this element. */

	virtual void add(Element* w);

	virtual void redraw();
	
	int getX() const  { return m_x; }
	int getY() const  { return m_y; }
	int getW() const  { return m_w; }
	int getH() const  { return m_h; }
	int getXW() const { return m_x + m_w; }
	int getYH() const { return m_y + m_h; }

	void setBounds(int x, int y, int w, int h);

protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* parent
	Widgets belong to a parent, that is a Window or another Element (groups). */

	Element* m_parent;

	/* window
	The top window this widgets belongs to. For windows, this is null. */

	Window* m_window;

	/* elements
	Lists of children elements contained into this Element. */

	std::vector<Element*> m_elements;

	Element(int x=0, int y=0, int w=0, int h=0);

	virtual void drawChildren();

private:

	Window* getParentWindow();

};
} // gg::


#endif
