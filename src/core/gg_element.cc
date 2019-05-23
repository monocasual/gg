#include <cassert>
#include "gg_element.hh"
#include "gg_events.hh"
#include "gg_window.hh"


namespace gg 
{
Element::Element(int x, int y, int w, int h)
: m_x     (x),
  m_y     (y),
  m_w     (w),
  m_h     (h),
  m_parent(nullptr),
  m_mouseDown(false)
{
}


/* -------------------------------------------------------------------------- */


void Element::handle(const SDL_Event& e)
{
    if (e.type & (SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP))
    {
        const MouseEvent me = makeMouseEvent();

        if (e.type == SDL_MOUSEBUTTONDOWN) 
        {
            for (Element* el : m_elements)
            {
                if (me.isOver(*el))
                {
                    el->m_mouseDown = true;
                    el->mouseDown();
                    el->redraw();
                    break;
                }
            }
        }
        else
        if (e.type == SDL_MOUSEBUTTONUP)
        {
            for (Element* el : m_elements)
            {
                if (el->m_mouseDown)
                {
                    el->m_mouseDown = false;
                    el->redraw();
                    el->mouseUp(me);
                    break;              
                }
            }
        }
    }
}


/* -------------------------------------------------------------------------- */


void Element::add(Element& e)
{
    add(&e);
}


void Element::add(Element* e)
{
    m_elements.push_back(e);
    e->m_parent = this;
}


/* -------------------------------------------------------------------------- */


void Element::redraw()
{
    Window* w = getParentWindow();
	draw(w->m_ren);
    w->render();
}


/* -------------------------------------------------------------------------- */


void Element::setBounds(int x, int y, int w, int h)
{
	m_x = x; m_y = y; m_w = w; m_h = h;
}


/* -------------------------------------------------------------------------- */


Window* Element::getParentWindow()
{
	/* Call getParentWindow() recursively until no parent found. Elements with no
	parents are Windows! */
	return m_parent == nullptr ? static_cast<Window*>(this) : m_parent->getParentWindow(); 
}


/* -------------------------------------------------------------------------- */


void Element::drawChildren(Renderer& ren)
{
	for (Element* e : m_elements)
		e->draw(ren);
}

} // gg::