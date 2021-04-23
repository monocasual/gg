#ifndef GG_ALERT_HH
#define GG_ALERT_HH

#include "core/gg_window.hh"
#include "gg_box.hh"
#include <functional>

namespace gg
{
class Alert : public Window
{
public:
	Alert(const std::string& title, const std::string& text);

	void resized() override;
	void closed() override;

private:
	Box m_box;
};
} // namespace gg

#endif
