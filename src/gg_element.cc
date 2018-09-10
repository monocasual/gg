#include "gg_element.hh"
#include "gg_widget.hh"


namespace gg 
{
Element::Element() 
: ren    (nullptr)
{
}


/* -------------------------------------------------------------------------- */


Element::~Element()
{
	for (Widget* w : m_widgets)
		delete w;
	m_widgets.clear();
	puts("[~Element] destroyed");
}


/* -------------------------------------------------------------------------- */


void Element::add(Widget& w)
{
	add(w);
}


void Element::add(Widget* w)
{
	m_widgets.push_back(w);
	w->setParent(this);
	printf("[Element::add] stack expanded, size=%zd\n", m_widgets.size());
}


/* -------------------------------------------------------------------------- */


void Element::redraw(Widget* w)
{
	w->draw(ren);
}


/* -------------------------------------------------------------------------- */


void Element::drawChildren()
{
	for (Widget* w : m_widgets)
		w->draw(ren);
}

} // gg::