#ifndef __GG_BUTTON_HH__
#define __GG_BUTTON_HH__


#include "gg_widget.hh"


class ggButton : public ggWidget
{
private:

	SDL_Rect rect;

	void drawDown();

public:

	ggButton(int x, int y, int w, int h, const char *l=NULL);

	void resize(int w, int h);
	void draw  ();
	void handle(SDL_Event &e);
};


#endif
