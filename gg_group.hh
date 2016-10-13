#ifndef __GG_GROUP_HH__
#define __GG_GROUP_HH__


#include "gg_baseGroup.hh"
#include "gg_widget.hh"


class ggGroup : public ggBaseGroup, public ggWidget
{
public:

	ggGroup(int x, int y, int w, int h);

	int add(ggWidget *w);

	void draw  ();
	void handle(SDL_Event &e);
};


#endif
