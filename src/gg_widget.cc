#include <SDL2/SDL.h>
#include "gg_widget.hh"
#include "gg_window.hh"


namespace gg 
{
Widget::Widget(int x, int y, int w, int h, const char* l)
	: m_x       (x),
		m_y       (y),
		m_w       (w),
		m_h       (h),
		m_label   (l),
		m_resizeW (false),
		m_resizeH (false),
		m_window  (nullptr)
{
}


/* -------------------------------------------------------------------------- */


Widget::~Widget()
{
}


/* -------------------------------------------------------------------------- */


int Widget::getX() const  { return m_x; }
int Widget::getY() const  { return m_y; }
int Widget::getW() const  { return m_w; }
int Widget::getH() const  { return m_h; }
int Widget::getXW() const { return m_x + m_w; }
int Widget::getYH() const { return m_y + m_h; }


/* -------------------------------------------------------------------------- */


bool Widget::isResizableW() const { return m_resizeW; }
bool Widget::isResizableH() const { return m_resizeH; }


void Widget::setResizable(bool rw, bool rh) 
{ 
	m_resizeW = rw; 
	m_resizeH = rh;
}


/* -------------------------------------------------------------------------- */


void Widget::resize(int w, int h)
{
	m_w = w;
	m_h = h;
}


/* -------------------------------------------------------------------------- */


void Widget::addWindow(Window* w) 
{ 
	m_window = w; 
}
} // g::