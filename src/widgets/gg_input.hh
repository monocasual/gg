#ifndef GG_INPUT_HH
#define GG_INPUT_HH


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

	std::string m_text;
};
} // gg::


#endif
