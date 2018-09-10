#include <SDL2/SDL.h>
#include "gg_widget.hh"
#include "gg_window.hh"


namespace gg 
{
Widget::Widget() : m_parent(nullptr)
{
}


/* -------------------------------------------------------------------------- */


Widget::~Widget()
{
}


/* -------------------------------------------------------------------------- */


void Widget::redraw()
{
	m_parent->redraw(this);
}


/* -------------------------------------------------------------------------- */


int Widget::getX() const  { return m_x; }
int Widget::getY() const  { return m_y; }
int Widget::getW() const  { return m_w; }
int Widget::getH() const  { return m_h; }
int Widget::getXW() const { return m_x + m_w; }
int Widget::getYH() const { return m_y + m_h; }


/* -------------------------------------------------------------------------- */


void Widget::setParent(Element* b) 
{ 
	m_parent = b; 
}


/* -------------------------------------------------------------------------- */


void Widget::setBounds(int x, int y, int w, int h)
{
	m_x = x; m_y = y; m_w = w; m_h = h;
}

} // g::