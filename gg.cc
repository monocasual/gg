#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gg.hh"


/* run
 * whether the app is running or not. */

static bool run;

/* stack
 * array of pointers to windows. */

static std::vector<ggWindow*> stack;

/* font
 * pointer to a TTF resource. */

static TTF_Font *font;

static gg_fontInfo fi;


/* -------------------------------------------------------------------------- */


int gg_init()
{
	run  = false;
	font = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("[gg::init] unable to initialize: %s\n", SDL_GetError());
		return 0;
	}
	if (TTF_Init() == -1)
	{
		printf("[gg::init] unable to initialize text rendering: %s\n", TTF_GetError());
		return 0;
	}
	run = true;
	return 1;
}


/* -------------------------------------------------------------------------- */


int gg_loadFont(const char *f, int s)
{
	font = TTF_OpenFontIndex(f, s, 0);
	if (!font)
	{
		printf("[ggWidget::setFont] unable to load font: %s\n", TTF_GetError());
		return 0;
	}
	fi.height = TTF_FontHeight(font);
	return 1;
}


/* -------------------------------------------------------------------------- */


gg_fontInfo &gg_getFontInfo()
{
	return fi;
}


/* -------------------------------------------------------------------------- */


void gg_drawFont(SDL_Renderer *ren, SDL_Rect rc, const char *t)
{
	SDL_Color color      = { 255, 255, 255 };
	SDL_Surface *surf    = TTF_RenderText_Solid(font, t, color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf);

	int tw, th;
	TTF_SizeText(font, t, &tw, &th);

	if (tw > rc.w)
		printf("[gg_drawFont] warning: string overflow (%d px)\n", tw - rc.w);

	rc.x = rc.x + (rc.w / 2) - (tw / 2);
	rc.y = rc.y + (rc.h / 2) - (th / 2);
	rc.w = tw;
	rc.h = th;

	SDL_RenderCopy(ren, texture, NULL, &rc);
}


/* -------------------------------------------------------------------------- */


void gg_freeFont()
{
	TTF_CloseFont(font);
}


/* -------------------------------------------------------------------------- */


int gg_run()
{
	SDL_Event e;
	while (run)
	{
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT)
		{
			puts("[gg::run] SDL_QUIT event, stop event loop");
			run = false;
		}
		else
		{
			for (unsigned i=0; i<stack.size(); i++)
				stack[i]->handle(e);
		}
	}
	gg_end();
	return 1;
}


/* -------------------------------------------------------------------------- */


void gg_add(ggWindow *w)
{
	stack.push_back(w);
	printf("[gg::add] add window %p, id=%d, stack size %zd\n",
		(void*)w, w->id, stack.size());
}


/* -------------------------------------------------------------------------- */


void gg_end()
{
	for (unsigned i=0; i<stack.size(); i++)
		delete stack[i];
	stack.clear();
	SDL_Quit();
	TTF_Quit();
}
