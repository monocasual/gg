#ifndef GG_ALERT_HH
#define GG_ALERT_HH


#include <functional>
#include "../core/gg_window.hh"
#include "gg_box.hh"


namespace gg
{
class Alert : public Window
{
public:

	Alert(const std::string& title, const std::string& text);

    void resized() override;

private:

    Box m_box;

};
} // gg::


#endif
