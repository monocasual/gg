#include "gg_baseGroup.hh"
#include "gg_widget.hh"


namespace gg 
{
BaseGroup::BaseGroup() 
: ren      (nullptr),
	damaged  (false)
{
}


/* -------------------------------------------------------------------------- */


BaseGroup::~BaseGroup()
{
	for (Widget* w : m_widgets)
		delete w;
	m_widgets.clear();
	puts("[~BaseGroup] destroyed");
}


/* -------------------------------------------------------------------------- */


void BaseGroup::add(Widget* w)
{
	m_widgets.push_back(w);
	w->setParent(this);
	printf("[BaseGroup::add] stack expanded, size=%zd\n", m_widgets.size());
}


/* -------------------------------------------------------------------------- */


void BaseGroup::drawChildren(int dw, int dh)
{
	for (Widget* w : m_widgets)
	{
		if (w->isResizableW() && w->isResizableH())
			w->resize(w->getW() + dw, w->getH() + dh);
		else
		if (w->isResizableW())
			w->resize(w->getW() + dw, w->getH());
		else
		if (w->isResizableH())
			w->resize(w->getW(), w->getH() + dh);
		w->draw();  // Redraw all widgets.
	}
}

} // gg::