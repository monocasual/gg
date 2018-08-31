#include "gg_baseGroup.hh"
#include "gg_widget.hh"


namespace gg 
{
BaseGroup::BaseGroup() {}


/* -------------------------------------------------------------------------- */


BaseGroup::~BaseGroup()
{
	for (Widget* w : m_stack)
		delete w;
	m_stack.clear();
	puts("[~BaseGroup] destroyed");
}


/* -------------------------------------------------------------------------- */


int BaseGroup::add(Widget* w)
{
	m_stack.push_back(w);
	printf("[BaseGroup::add] stack expanded, size=%zd\n", m_stack.size());
	return 1;
}


/* -------------------------------------------------------------------------- */


void BaseGroup::drawChildren(int dw, int dh)
{
	for (Widget* w : m_stack)
	{
		if (w->resizableW() && w->resizableH())
			w->resize(w->w() + dw, w->h() + dh);
		else
		if (w->resizableW())
			w->resize(w->w() + dw, w->h());
		else
		if (w->resizableH())
			w->resize(w->w(), w->h() + dh);
		w->draw();  // Redraw all widgets.
	}
}

} // gg::