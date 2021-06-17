#ifndef GG_CONST_HH
#define GG_CONST_HH

#include "gg_types.hh"

namespace gg
{
constexpr auto GG_DEFAULT_FONT_PATH = "extras/fonts/OpenSans-Regular.ttf";
constexpr auto GG_DEFAULT_FONT_SIZE = 16;

constexpr Color GG_WINDOW_BACKGROUND_COLOR         = Color{30, 30, 30};
constexpr Color GG_ELEMENT_BACKGROUND_COLOR        = Color{20, 20, 20};
constexpr Color GG_ELEMENT_BOUNDARY_COLOR          = Color{220, 220, 220};
constexpr Color GG_ELEMENT_BOUNDARY_COLOR_DISABLED = Color{80, 80, 80};
} // namespace gg

#endif