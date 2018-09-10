#ifndef GG_WINDOW_HH
#define GG_WINDOW_HH


#include <SDL2/SDL.h>
#include "gg_baseGroup.hh"


namespace gg 
{
class Widget;


class Window : public BaseGroup
{
protected:

	/* xywh
	Main coordinates. */

	int m_x, m_y, m_w, m_h;

	/* win
	Pointer to a SDL_Window structure. */

	SDL_Window* m_win;

	/* preW, preH
	Previous width and height for calculating increments. */

	int m_preW, m_preH;

public:

	/* id
	Unique id of this window. */

	unsigned id;

	Window(const char* t, int x, int y, int w, int h);
	~Window();

	/* xywh()
	Sets and return coordinates. */

	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;
	
	void setX(int x);
	void setY(int y);

	void resize(int w, int h);

	/* show()
	Shows the window on screen. */

	void show();

	/* clear()
	Deletes all widget from screen and cover it with the regular background. */

	void clear();

	/* drawChildren()
	Calls draw() for each child in the group. */

	void drawChildren();

	/* render()
	Updates the screen after the children have been drawn. */

	void render();

	/* handle()
	Handles window events such as shown, a resize, a popup and so on. */
	
	void handle(const SDL_Event& e);
};
} // gg::


#endif