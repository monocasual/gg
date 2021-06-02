#ifndef GG_STYLE_HH
#define GG_STYLE_HH

#include "gg_const.hh"
#include "gg_types.hh"
#include <string>

namespace gg
{
struct Style
{
	virtual std::string fontPath() const { return GG_DEFAULT_FONT_PATH; }
	virtual int         fontSize() const { return 16; }

	virtual Color windowBackgroundColor() const { return Color{30, 30, 30}; }

	virtual Color boxBoundaryColor() const { return Color{255, 255, 255}; }
	virtual Color boxBackgroundColor() const { return Color{30, 30, 30}; }

	virtual Color buttonBoundaryColor() const { return Color{255, 255, 255}; }
	virtual Color buttonBackgroundColorDown() const { return Color{100, 100, 100}; }
	virtual Color buttonBackgroundColorUp() const { return Color{0, 0, 0}; }

	virtual Color inputBackgroundColor() const { return Color{10, 10, 10}; }
	virtual Color inputTextColor() const { return Color{255, 255, 255}; }
	virtual Color inputFocusColor() const { return Color{150, 150, 150}; }

	virtual Color sliderBackgroundColor() const { return Color{0, 0, 0}; }
	virtual Color sliderBodyColor() const { return Color{255, 255, 255}; }

	virtual Color scrollbarBackgroundColor() const { return Color{20, 20, 20}; }
	virtual Color scrollbarBodyColor() const { return Color{220, 220, 220}; }

	virtual Color viewportBoundaryColor() const { return Color{255, 255, 255}; }
};
} // namespace gg

#endif