#ifndef GG_INPUT_HH
#define GG_INPUT_HH

#include "core/gg_element.hh"
#include "deps/tiny-utf8/include/tinyutf8/tinyutf8.h"

namespace gg
{
class Renderer;
class Input : public Element
{
public:
	Input();

	void draw(Renderer& ren) override;
	void keyPress(const KeyEvent& e) override;
	void mouseDown(const MouseEvent&) override;

private:
	int getCaretPx(const Renderer& ren) const;

	tiny_utf8::string            m_text;
	tiny_utf8::string::size_type m_caret;
};
} // namespace gg

#endif
