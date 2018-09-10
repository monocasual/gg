
/* BaseGroup -----------------------------------------------------------------
 *
 * A generic base for every group.
 *
 * -------------------------------------------------------------------------- */


#ifndef GG_BASEGROUP_HH
#define GG_BASEGROUP_HH


#include <vector>


namespace gg 
{
class Widget;


class BaseGroup
{
protected:

	std::vector<Widget*> m_stack;

	BaseGroup();

public:

	virtual ~BaseGroup();

	virtual void add(Widget* w);

	virtual void drawChildren(int dw, int dh);
};
} // gg::


#endif
