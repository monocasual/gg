#include "gg_baseGroup.hh"
#include "gg_widget.hh"


namespace gg 
{
BaseGroup::BaseGroup() {}


/* -------------------------------------------------------------------------- */


BaseGroup::~BaseGroup()
{
	for (unsigned i=0; i<m_stack.size(); i++)
		delete m_stack[i];
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
	for (unsigned i=0; i<m_stack.size(); i++)
	{
		if (m_stack[i]->resizableW() && m_stack[i]->resizableH())
			m_stack[i]->resize(m_stack[i]->w() + dw, m_stack[i]->h() + dh);
		else
		if (m_stack[i]->resizableW())
			m_stack[i]->resize(m_stack[i]->w() + dw, m_stack[i]->h());
		else
		if (m_stack[i]->resizableH())
			m_stack[i]->resize(m_stack[i]->w(), m_stack[i]->h() + dh);

		/* redraw all widgets */

		m_stack[i]->draw();
	}
}

} // gg::