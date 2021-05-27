#ifndef GG_STYLE_HH
#define GG_STYLE_HH

#include "gg_const.hh"
#include "gg_types.hh"
#include <string>

namespace gg
{
struct Style
{
	std::string fontPath = GG_DEFAULT_FONT_PATH;
	int         fontSize = 16;

	Color windowBackgroundColor = Color{30, 30, 30};

	Color boxBoundaryColor   = Color{255, 255, 255};
	Color boxBackgroundColor = Color{30, 30, 30};

	Color buttonBoundaryColor       = Color{255, 255, 255};
	Color buttonBackgroundColorDown = Color{100, 100, 100};
	Color buttonBackgroundColorUp   = Color{0, 0, 0};

	Color inputBackgroundColor = Color{10, 10, 10};
	Color inputTextColor       = Color{255, 255, 255};
	Color inputFocusColor      = Color{150, 150, 150};

	Color sliderBackgroundColor = Color{0, 0, 0};
	Color sliderBodyColor       = Color{255, 255, 255};
};
} // namespace gg

#endif