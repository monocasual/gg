
/* ggBaseGroup -----------------------------------------------------------------
 *
 * A generic base for every group.
 *
 * -------------------------------------------------------------------------- */


#ifndef __GG_BASEGROUP_HH__
#define __GG_BASEGROUP_HH__


#include <vector>
#include "gg_widget.hh"


class ggBaseGroup
{
protected:

	std::vector<ggWidget*> stack;

public:

	ggBaseGroup();
	virtual ~ggBaseGroup();

	virtual int add(class ggWidget *w);

	virtual void drawChildren(int dw, int dh);
};


#endif
