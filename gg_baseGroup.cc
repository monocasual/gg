#include "gg_baseGroup.hh"
#include "gg_widget.hh"


ggBaseGroup::ggBaseGroup() {}


/* -------------------------------------------------------------------------- */


ggBaseGroup::~ggBaseGroup()
{
	for (unsigned i=0; i<stack.size(); i++)
		delete stack[i];
	stack.clear();
	puts("[~ggBaseGroup] destroyed");
}


/* -------------------------------------------------------------------------- */


int ggBaseGroup::add(ggWidget *w)
{
	stack.push_back(w);
	printf("[ggBaseGroup::add] stack expanded, size=%zd\n", stack.size());
	return 1;
}


/* -------------------------------------------------------------------------- */


void ggBaseGroup::drawChildren(int dw, int dh)
{
	for (unsigned i=0; i<stack.size(); i++)
	{
		if (stack[i]->resizableW() && stack[i]->resizableH())
			stack[i]->resize(stack[i]->w() + dw, stack[i]->h() + dh);
		else
		if (stack[i]->resizableW())
			stack[i]->resize(stack[i]->w() + dw, stack[i]->h());
		else
		if (stack[i]->resizableH())
			stack[i]->resize(stack[i]->w(), stack[i]->h() + dh);

		/* redraw all widgets */

		stack[i]->draw();
	}
}
