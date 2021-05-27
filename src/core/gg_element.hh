/* Element ---------------------------------------------------------------------

A generic base for everything.

----------------------------------------------------------------------------- */

#ifndef GG_ELEMENT_HH
#define GG_ELEMENT_HH

#include "deps/geompp/src/rect.hpp"
#include "gg.hh"
#include "gg_style.hh"
#include <SDL2/SDL.h>
#include <vector>

namespace gg
{
class Window;
class Renderer;
struct MouseEvent;
struct KeyEvent;
class Element
{
public:
	virtual ~Element(){};

	/* handle() [virtual]
	Fired on events such as click, keypress, window show-hide and so on. */

	virtual void handle(const SDL_Event& e);

	/* resized() [virtuals]
	Fired when the element position and size change. */

	virtual void resized(){};

	/* draw() [virtual]
	Drawing routines. This method draws the initial graphical state of each 
	widget. */

	virtual void draw(Renderer& ren);

	virtual void mouseDown(const MouseEvent&){};
	virtual void mouseUp(const MouseEvent&){};
	virtual void mouseMove(const MouseEvent&){};
	virtual void mouseDrag(const MouseEvent&){};

	virtual void keyPress(const KeyEvent&){};

	/* redraw() [virtual]
	Forces the redraw for this element and all its children. */

	virtual void redraw();

	//virtual const Style& getStyle() const;

	/* add()
	Adds a child widget to this element. */

	void add(Element* w);
	void add(Element& w);

	int               getX() const { return m_bounds.x; }
	int               getY() const { return m_bounds.y; }
	int               getW() const { return m_bounds.w; }
	int               getH() const { return m_bounds.h; }
	int               getXW() const { return m_bounds.xw; }
	int               getYH() const { return m_bounds.yh; }
	geompp::Rect<int> getBounds() const { return m_bounds; }

	void setBounds(int x, int y, int w, int h);
	void setBounds(geompp::Rect<int> b);

	/* setFocus()
	Set focus to this element. Other children lose their focus. */

	void setFocus();

	/* clearFocus()
	Clear focus for this elements and all children. */

	void clearFocus();

protected:
	Element(geompp::Rect<int> r = {});

	/* drawChildren [virtual]
	Draws all children of this element. */

	virtual void drawChildren(Renderer& ren);

	Window* getParentWindow();

	/* m_bounds
	Main coordinates. */

	geompp::Rect<int> m_bounds;

	/* parent
	Widgets belong to a parent, that is a Window or another Element (groups). */

	Element* m_parent;

	/* elements
	Lists of children elements contained into this Element. */

	std::vector<Element*> m_elements;

	//Style m_style;

	/* m_mouseDown
	Tells whether the mouse has been held down on this element. */

	bool m_mouseDown;

	/* m_focus
	Tells whether this element has focus. Focus is gained by clicling on it. */

	bool m_focus;
};
} // namespace gg

#endif
