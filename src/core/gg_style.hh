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
	virtual int         fontSize() const { return GG_DEFAULT_FONT_SIZE; }

	virtual Color windowBackgroundColor() const { return GG_WINDOW_BACKGROUND_COLOR; }

	virtual Color boxBoundaryColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }
	virtual Color boxBackgroundColor() const { return GG_ELEMENT_BACKGROUND_COLOR; }

	virtual Color buttonBoundaryColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }
	virtual Color buttonBackgroundColorDown() const { return Color{100, 100, 100}; }
	virtual Color buttonBackgroundColorUp() const { return GG_ELEMENT_BACKGROUND_COLOR; }

	virtual Color inputBackgroundColor() const { return GG_ELEMENT_BACKGROUND_COLOR; }
	virtual Color inputTextColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }
	virtual Color inputFocusColor() const { return Color{150, 150, 150}; }

	virtual Color sliderBackgroundColor() const { return GG_ELEMENT_BACKGROUND_COLOR; }
	virtual Color sliderBodyColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }

	virtual Color scrollbarBackgroundColor() const { return GG_ELEMENT_BACKGROUND_COLOR; }
	virtual Color scrollbarBodyColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }

	virtual Color viewportBoundaryColor() const { return GG_ELEMENT_BOUNDARY_COLOR; }
};
} // namespace gg

#endif