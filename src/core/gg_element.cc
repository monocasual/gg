#include <cassert>
#include "gg_element.hh"
#include "gg_events.hh"
#include "gg_window.hh"


namespace gg 
{
Element::Element(Rect r)
: m_bounds   (r)
, m_parent   (nullptr)
, m_mouseDown(false)
, m_focus    (false)
{
}


/* -------------------------------------------------------------------------- */


void Element::handle(const SDL_Event& e)
{
    if (e.window.windowID != getParentWindow()->id)
        return;

    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
    {
        const MouseEvent me = makeMouseEvent();

        if (e.type == SDL_MOUSEBUTTONDOWN && me.isOver(m_bounds)) 
        {
            m_mouseDown = true;
            setFocus();
            mouseDown(me);
            redraw();
        }
        else
        if (e.type == SDL_MOUSEBUTTONUP && m_mouseDown)
        {
            m_mouseDown = false;
            redraw();
            mouseUp(me);
        }       
    }
    else
    if (e.type == SDL_MOUSEMOTION)
    {
        const MouseEvent me = makeMouseEvent();
        if (m_mouseDown)
        {
            mouseDrag(me);
            redraw();
        }
        else
        if (me.isOver(m_bounds))
        {
            mouseMove(me);
            redraw();       
        }
    }
    else
    if (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT)
    {
        /* Generic press: includes also special keys (backspace, tab, ...).
        More information: 
        https://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php */

        if (e.type == SDL_KEYDOWN)
        {
            if (m_focus && e.key.keysym.sym == SDLK_BACKSPACE)
                keyPress(makeFuncKeyEvent(KeyEvent::Type::BACKSPACE));
        }
        else // SDL_TEXTINPUT
        {
            if (m_focus)
                keyPress(makeTextKeyEvent(e));
        }

        redraw();
    }

    /* Pass the event to the underlying children. */

    for (Element* el : m_elements)
        el->handle(e);
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
    /* On redraw() all elements inside the window are redrawn. A future 
    optimization will paint only those elements with a damaged state: see
    drawChildren() below. */

    Window* w = getParentWindow();
    w->clear();
    w->drawChildren(w->m_ren);
    w->render();
}


/* -------------------------------------------------------------------------- */


void Element::draw(Renderer& ren)
{
    ren.setClip(m_bounds);
    drawChildren(ren);
    ren.unsetClip();
}


/* -------------------------------------------------------------------------- */


void Element::setBounds(int x, int y, int w, int h)
{
    m_bounds = Rect(x, y, w, h);
    resized();
}


void Element::setBounds(Rect b)
{
    setBounds(b.x, b.y, b.w, b.h);
}


/* -------------------------------------------------------------------------- */


void Element::setFocus()
{
    for (Element* el : m_elements)
        el->m_focus = false;
    m_focus = true;
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
    /* TODO - damage flag: redraw only if damaged */
	for (Element* e : m_elements)
		e->draw(ren);
}
} // gg::