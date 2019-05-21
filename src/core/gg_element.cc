#include <cassert>
#include "gg_element.hh"
#include "gg_window.hh"


namespace gg 
{
Element::Element(int x, int y, int w, int h)
: m_x     (x),
  m_y     (y),
  m_w     (w),
  m_h     (h),
  m_parent(nullptr)
{
}


/* -------------------------------------------------------------------------- */


Element::~Element()
{
	for (Element* e : m_elements)
		delete e;
	m_elements.clear();
}


/* -------------------------------------------------------------------------- */


void Element::handle(const SDL_Event& e)
{
    for (Element* el : m_elements)
        el->handle(e);
}


/* -------------------------------------------------------------------------- */


void Element::add(Element* e)
{
	m_elements.push_back(e);
	e->m_parent = this;
}


/* -------------------------------------------------------------------------- */


void Element::redraw()
{
    Window* w = getParentWindow();
	draw(w->m_ren);
    w->render();
}


/* -------------------------------------------------------------------------- */


void Element::setBounds(int x, int y, int w, int h)
{
	m_x = x; m_y = y; m_w = w; m_h = h;
}


/* -------------------------------------------------------------------------- */


Window* Element::getParentWindow()
{
	/* Call getParentWindow() recursively until no parent found. Elements with no
	parents are Windows! */
	return m_parent == nullptr ? static_cast<Window*>(this) : m_parent->getParentWindow(); 
}


/* -------------------------------------------------------------------------- */


void Element::drawChildren(Renderer& ren)
{
	for (Element* e : m_elements)
		e->draw(ren);
}

} // gg::