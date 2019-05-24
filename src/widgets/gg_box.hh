#ifndef GG_BOX_HH
#define GG_BOX_HH


#include "../core/gg_element.hh"


namespace gg
{
class Renderer;
class Box : public Element
{
public:

	Box(const char* l=nullptr);

	void draw(Renderer& ren) override;

private:

	const char* m_label;
};
} // gg::


#endif
