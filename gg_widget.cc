#include <SDL2/SDL.h>
#include "gg_widget.hh"
#include "gg_window.hh"


ggWidget::ggWidget(int x, int y, int w, int h, const char *l)
	: _x (x),
		_y (y),
		_w (w),
		_h (h),
		_xw(x+w),
		_yh(y+h),
		window  (NULL),
		callback(NULL),
		label   (l),
		resizeW (false),
		resizeH (false)
{
}


/* ------------------------------------------------------------------ */


ggWidget::~ggWidget()
{
}


/* ------------------------------------------------------------------ */


void ggWidget::resize(int w, int h)
{
	_w = w;
	_h = h;
	_xw = _x+w;
	_yh = _y+h;
}


/* ------------------------------------------------------------------ */


void ggWidget::addCallback(ggCallback *cb, void *cbData)
{
	callback = cb;
	callbackData = cbData;
}


/* ------------------------------------------------------------------ */


void ggWidget::doCallback()
{
	if (callback)
		(*callback)(callbackData);
}
