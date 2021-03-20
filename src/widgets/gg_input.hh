#ifndef GG_INPUT_HH
#define GG_INPUT_HH


#include "deps/tiny-utf8/include/tinyutf8/tinyutf8.h"
#include "core/gg_element.hh"


namespace gg
{
class Renderer;
class Input : public Element
{
public:

	Input();

	void draw(Renderer& ren) override;
	void keyPress(const KeyEvent& e) override;

private:

	int getCaretPx(const Renderer& ren) const;

	tiny_utf8::string m_text;
	int               m_caret;
};
} // gg::


#endif
