
/* ggBaseGroup ---------------------------------------------------------
 *
 * A generic base for every group.
 *
 * ------------------------------------------------------------------ */


#ifndef __GG_BASEGROUP_HH__
#define __GG_BASEGROUP_HH__


class ggBaseGroup
{
protected:

	class ggWidget **stack;
	int              size;

public:

	ggBaseGroup();
	virtual ~ggBaseGroup();

	virtual int add(class ggWidget *w);

	virtual void drawChildren(int dw, int dh);
};


#endif
