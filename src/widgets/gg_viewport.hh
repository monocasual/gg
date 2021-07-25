#ifndef GG_VIEWPORT_HH
#define GG_VIEWPORT_HH

#include "atoms/gg_box.hh"
#include "atoms/gg_scrollbar.hh"
#include "core/gg_element.hh"
#include <functional>

namespace gg
{
class Renderer;
class Viewport : public Element
{
public:
	enum class Direction
	{
		VERTICAL,
		HORIZONTAL,
		BOTH
	};

	/* Frame
	An element container that clips its content and moves it around. */

	class Frame : public Element
	{
	public:
		void draw(Renderer& ren) override;
		void resized() override;

		/* getCoveredPoint
		Returns the bottom-left point (x, y) of the contained element that is 
		currently being covered by the frame. Positive values: the element is
		partially hidden. Negative values: the element is fully visible. */

		geompp::Point<int> getCoveredPoint() const;

		const Element* getContent() const;
		bool           hasContent() const;

		void     setContent(Element& e, int w, int h);
		Element* getContent();

		/* moveContent...
		Moves content to a specific position. Origin starts at {0, 0}. */

		void moveContent(geompp::Point<int> p);
		void moveContentX(int x);
		void moveContentY(int y);

		/* onMovedContent
		Callback fired when the content is moved internally by this Frame (and
		not when moveContent...() is called). */

		std::function<void(geompp::Point<int>)> onMovedContent = nullptr;

	private:
		void onContent(std::function<void(Element&)> f);
	};

	Viewport(Direction d = Direction::BOTH);

	void resized() override;

	void     setContent(Element& e, int w, int h);
	Element* getContent();

private:
	static constexpr int SCROLLBAR_SIZE = 20;

	Direction m_direction;
	Frame     m_frame;
	Scrollbar m_vscrollbar;
	Scrollbar m_hscrollbar;
};
} // namespace gg

#endif
