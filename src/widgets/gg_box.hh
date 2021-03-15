#ifndef GG_BOX_HH
#define GG_BOX_HH


#include <string>
#include "core/gg_element.hh"


namespace gg
{
class Renderer;
class Box : public Element
{
public:

	Box(std::string t="");

	void draw(Renderer& ren) override;

    void setText(std::string t);

private:

	std::string m_text;
};
} // gg::


#endif
