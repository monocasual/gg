#include "gg_baseGroup.hh"
#include "gg_widget.hh"


ggBaseGroup::ggBaseGroup()
	: stack(NULL), size(0)
{
}


/* ------------------------------------------------------------------ */


ggBaseGroup::~ggBaseGroup()
{
	for (int i=0; i<size; i++)
		delete stack[i];
	free(stack);
	puts("[~ggBaseGroup] destroyed");
}


/* ------------------------------------------------------------------ */


int ggBaseGroup::add(ggWidget *w)
{
	stack = (ggWidget**) realloc(stack, sizeof(w)*(size+1));
	if (!stack)
	{
		printf("[ggBaseGroup::add] unable to expand stack!\n");
		return 0;
	}
	stack[size] = w;
	size++;
	printf("[ggBaseGroup::add] stack expanded, size=%d sizeof(stack)=%d\n", size, sizeof(w)*size);
	return 1;
}


/* ------------------------------------------------------------------ */


void ggBaseGroup::drawChildren(int dw, int dh)
{
	for (int i=0; i<size; i++)
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
