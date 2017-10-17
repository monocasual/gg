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
		m_xw      (x+w),
		m_yh      (y+h),
		m_label   (l),
		m_resizeW (false),
		m_resizeH (false),
		m_window  (nullptr),
		m_callback(nullptr)
{
}


/* -------------------------------------------------------------------------- */


Widget::~Widget()
{
}


/* -------------------------------------------------------------------------- */


int Widget::x() const  { return m_x; }
int Widget::y() const  { return m_y; }
int Widget::w() const  { return m_w; }
int Widget::h() const  { return m_h; }
int Widget::xw() const { return m_xw; }
int Widget::yh() const { return m_yh; }


/* -------------------------------------------------------------------------- */


bool Widget::resizableW() const { return m_resizeW; }
bool Widget::resizableH() const { return m_resizeH; }


void Widget::resizable(bool rw, bool rh) 
{ 
	m_resizeW = rw; 
	m_resizeH = rh;
}


/* -------------------------------------------------------------------------- */


void Widget::resize(int w, int h)
{
	m_w = w;
	m_h = h;
	m_xw = m_x+w;
	m_yh = m_y+h;
}


/* -------------------------------------------------------------------------- */


void Widget::addCallback(callback_t* cb, void* cbData)
{
	m_callback = cb;
	m_callbackData = cbData;
}


/* -------------------------------------------------------------------------- */


void Widget::addWindow(Window* w) 
{ 
	m_window = w; 
}


/* -------------------------------------------------------------------------- */


void Widget::doCallback() const
{
	if (m_callback)
		(*m_callback)(m_callbackData);
}

} // g::