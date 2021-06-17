#include "gg_element.hh"
#include "gg_events.hh"
#include "gg_window.hh"
#include <cassert>

namespace gg
{
Element::Element(geompp::Rect<int> r)
: visible(true)
, m_bounds(r)
, m_parent(nullptr)
, m_mouseDown(false)
, m_focus(false)
, m_enabled(true)
{
}

/* -------------------------------------------------------------------------- */

void Element::handle(const SDL_Event& e)
{
	if (e.window.windowID != getParentWindow()->id || !visible || !m_enabled)
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
		else if (e.type == SDL_MOUSEBUTTONUP && m_mouseDown)
		{
			m_mouseDown = false;
			redraw();
			mouseUp(me);
		}
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		const MouseEvent me = makeMouseEvent();
		if (m_mouseDown)
		{
			mouseDrag(me);
			redraw();
		}
		else if (me.isOver(m_bounds))
		{
			mouseMove(me);
			redraw();
		}
	}
	else if (m_focus && (e.type == SDL_KEYDOWN || e.type == SDL_TEXTINPUT))
	{
		/* Generic press: includes also special keys (backspace, tab, ...).
        More information: 
        https://lazyfoo.net/tutorials/SDL/32_text_input_and_clipboard_handling/index.php */

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_BACKSPACE)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::BACKSPACE));
			else if (e.key.keysym.sym == SDLK_DELETE)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::DELETE));
			else if (e.key.keysym.sym == SDLK_UP)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::ARROW_UP));
			else if (e.key.keysym.sym == SDLK_DOWN)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::ARROW_DOWN));
			else if (e.key.keysym.sym == SDLK_LEFT)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::ARROW_LEFT));
			else if (e.key.keysym.sym == SDLK_RIGHT)
				keyPress(makeFuncKeyEvent(KeyEvent::Type::ARROW_RIGHT));
		}
		else // SDL_TEXTINPUT
		{
			keyPress(makeTextKeyEvent(e));
		}

		redraw();
	}

	/* Pass the event to the underlying children. */

	for (Element* el : m_elements)
		el->handle(e);
}

/* -------------------------------------------------------------------------- */

int Element::countElements() const
{
	return m_elements.size();
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
	if (!visible)
		return;
	ren.setClip(m_bounds);
	drawChildren(ren);
	ren.unsetClip();
}

/* -------------------------------------------------------------------------- */

void Element::setBounds(int x, int y, int w, int h)
{
	m_bounds = geompp::Rect<int>(x, y, w, h);
	resized();
}

void Element::setBounds(geompp::Rect<int> b)
{
	setBounds(b.x, b.y, b.w, b.h);
}

/* -------------------------------------------------------------------------- */

void Element::setFocus()
{
	if (!visible)
		return;
	clearFocus();
	m_focus = true;
}

/* -------------------------------------------------------------------------- */

void Element::clearFocus()
{
	if (!visible)
		return;
	for (Element* el : m_elements)
		el->m_focus = false;
	m_focus = false;
}

/* -------------------------------------------------------------------------- */

void Element::setEnabled(bool v)
{
	m_enabled = v;
	redraw();
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
		if (e->visible)
			e->draw(ren);
}
} // namespace gg