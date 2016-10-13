#include "gg_window.hh"


struct gg_fontInfo
{
	int height;
};


/* init()
 * */

int  gg_init();

/* add()
 * */

void gg_add(ggWindow *w);

/* run()
 * */

int  gg_run();

/* end()
 * */

void gg_end();

/* loadFont()
 * load a font for drawing text. */

int  gg_loadFont(const char *f, int size);

gg_fontInfo &gg_getFontInfo();

int  gg_drawFont(SDL_Renderer *ren, SDL_Rect rc, const char *t);

void gg_freeFont();
