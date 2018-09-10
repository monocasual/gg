#ifndef GG_GROUP_HH
#define GG_GROUP_HH


#include "gg_baseGroup.hh"
#include "gg_widget.hh"


namespace gg
{
class Group : public BaseGroup, public Widget
{
public:

	Group(int x, int y, int w, int h);

	void draw() override;
	void handle(const SDL_Event& e) override;
};
} // gg::


#endif
