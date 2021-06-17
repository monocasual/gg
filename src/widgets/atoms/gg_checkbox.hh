#ifndef GG_CHECKBOX_HH
#define GG_CHECKBOX_HH

#include "core/gg_element.hh"
#include <functional>
#include <string>

namespace gg
{
class Renderer;
class Checkbox : public Element
{
public:
	Checkbox(bool status, std::string t = "");

	void draw(Renderer& ren) override;
	void mouseUp(const MouseEvent& e) override;

	bool getStatus() const;

	void setStatus(bool s);

	std::function<void(bool)> onChange;

private:
	bool        m_status;
	std::string m_text;
};
} // namespace gg

#endif
