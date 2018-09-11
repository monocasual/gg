#include "gg_element.hh"


namespace gg 
{
Element::Element() 
: ren    (nullptr)
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
	printf("[Element::add] stack expanded, size=%zd\n", m_elements.size());
}


/* -------------------------------------------------------------------------- */


void Element::redraw()
{
	draw(ren);
}


/* -------------------------------------------------------------------------- */


void Element::setBounds(int x, int y, int w, int h)
{
	m_x = x; m_y = y; m_w = w; m_h = h;
}


/* -------------------------------------------------------------------------- */


void Element::drawChildren()
{
	for (Element* e : m_elements)
		e->draw(ren);
}

} // gg::