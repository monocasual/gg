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
	Input(const std::string& s = "");

	void draw(Renderer& ren) override;
	void keyPress(const KeyEvent& e) override;

	std::string getText() const;

	void setEditable(bool v);
	void setText(const std::string& s);

	std::function<void()> onChange;

private:
	int getCaretPx(const Renderer& ren) const;

	tiny_utf8::string            m_text;
	tiny_utf8::string::size_type m_caret;
	bool                         m_editable;
};
} // namespace gg

#endif
