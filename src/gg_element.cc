#include <cassert>
#include "gg_element.hh"
#include "gg_window.hh"


namespace gg 
{
Element::Element()
: m_parent(nullptr), 
  m_window(nullptr)
{
}


/* -------------------------------------------------------------------------- */


Element::~Element()
{
	for (Element* e : m_elements)
		delete e;
	m_elements.clear();
	puts("[~Element] destroyed");
}


/* -------------------------------------------------------------------------- */


void Element::add(Element* e)
{
	m_elements.push_back(e);
	e->m_parent = this;
	e->m_window = getParentWindow();

	printf("[Element::add] stack expanded, size=%zd, window=%p\n", 
		m_elements.size(), (void*) m_window);
}


/* -------------------------------------------------------------------------- */


void Element::redraw()
{
	draw(m_window->m_ren);
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


void Element::drawChildren()
{
	/* If this element has m_parent == null, this is the main window. So there is
	no m_window to pass to draw(). Let's use the one from the child element. */  
	for (Element* e : m_elements)
		e->draw(m_parent == nullptr ? e->m_window->m_ren : m_window->m_ren);
}

} // gg::