#include "gg_viewport.hh"
#include "core/gg_renderer.hh"
#include "deps/mcl-utils/src/math.hpp"

using namespace mcl;

namespace gg
{
void Viewport::Frame::draw(Renderer& ren)
{
	Element::draw(ren);

	ren.setColor(gg::getStyle().viewportBoundaryColor());
	ren.drawRect(m_bounds);
}

/* -------------------------------------------------------------------------- */

void Viewport::Frame::resized()
{
	if (!hasContent())
		return;

	/* Extremely brutal fix: on resize, the internal content's position get
	reset to {0, 0}. You might want something more gentle in the future. */

	moveContent({0, 0});

	/* Notify the movement has been done internally. */

	if (onMovedContent != nullptr)
		onMovedContent({0, 0});
}

/* -------------------------------------------------------------------------- */

geompp::Point<int> Viewport::Frame::getCoveredPoint() const
{
	const Element* content = getContent();
	if (content == nullptr)
		return {};

	return {
	    content->getBounds().w - m_bounds.w,
	    content->getBounds().h - m_bounds.h};
}

/* -------------------------------------------------------------------------- */

const Element* Viewport::Frame::getContent() const
{
	return m_elements.size() == 0 ? nullptr : m_elements[0];
}

/* -------------------------------------------------------------------------- */

bool Viewport::Frame::hasContent() const
{
	return getContent() != nullptr;
}

/* -------------------------------------------------------------------------- */

void Viewport::Frame::setContent(Element& e, int w, int h)
{
	if (m_elements.size() > 0) // Only one element allowed
		return;
	e.setBounds(getX(), getY(), w, h);
	add(e);
}

/* -------------------------------------------------------------------------- */

void Viewport::Frame::moveContent(geompp::Point<int> p)
{
	onContent([bp = getPosition(), p](Element& e)
	    { e.setPosition(bp + p); });
}

void Viewport::Frame::moveContentX(int x)
{
	onContent([bx = m_bounds.x, x](Element& e)
	    { e.setX(bx + x); });
}

void Viewport::Frame::moveContentY(int y)
{
	onContent([by = m_bounds.y, y](Element& e)
	    { e.setY(by + y); });
}

/* -------------------------------------------------------------------------- */

Element* Viewport::Frame::getContent()
{
	return const_cast<Element*>(const_cast<const Viewport::Frame*>(this)->getContent());
}

/* -------------------------------------------------------------------------- */

void Viewport::Frame::onContent(std::function<void(Element&)> f)
{
	Element* content = getContent();
	if (content != nullptr)
		f(*content);
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

Viewport::Viewport(Direction d)
: m_direction(d)
, m_vscrollbar(Scrollbar::Type::VERTICAL)
, m_hscrollbar(Scrollbar::Type::HORIZONTAL)
{
	add(m_frame);
	if (m_direction == Direction::VERTICAL || m_direction == Direction::BOTH)
		add(m_vscrollbar);
	if (m_direction == Direction::HORIZONTAL || m_direction == Direction::BOTH)
		add(m_hscrollbar);

	m_frame.onMovedContent = [this](geompp::Point<int>)
	{
		m_hscrollbar.setValue(0.0f, /*fireCallback=*/false);
		m_vscrollbar.setValue(0.0f, /*fireCallback=*/false);
	};

	m_hscrollbar.onChange = [this](float v)
	{
		m_frame.moveContentX(-utils::math::map(v, 1.0f, m_frame.getCoveredPoint().x));
	};

	m_vscrollbar.onChange = [this](float v)
	{
		m_frame.moveContentY(-utils::math::map(v, 1.0f, m_frame.getCoveredPoint().y));
	};
}

/* -------------------------------------------------------------------------- */

void Viewport::resized()
{
	m_frame.setBounds(m_bounds.withTrimmedRight(SCROLLBAR_SIZE).withTrimmedBottom(SCROLLBAR_SIZE));
	m_vscrollbar.setBounds(m_bounds.withTrimmedBottom(SCROLLBAR_SIZE).withTrimmedLeft(m_frame.getBounds().w));
	m_hscrollbar.setBounds(m_bounds.withTrimmedRight(SCROLLBAR_SIZE).withTrimmedTop(m_frame.getBounds().h));
}

/* -------------------------------------------------------------------------- */

void Viewport::setContent(Element& e, int w, int h)
{
	m_frame.setContent(e, w, h);
}

/* -------------------------------------------------------------------------- */

Element* Viewport::getContent()
{
	return m_frame.getContent();
}
} // namespace gg