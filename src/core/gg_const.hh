#ifndef GG_CONST_HH
#define GG_CONST_HH

#include <iostream>

namespace gg
{
constexpr auto GG_DEFAULT_FONT_PATH = "extras/fonts/OpenSans-Regular.ttf";

#ifndef NDEBUG
#define GG_DEBUG(x) std::cerr << __FILE__ << "::" << __func__ << "() - " << x << std::endl
#else
#define GG_DEBUG(x) \
	do              \
	{               \
	} while (0)
#endif
} // namespace gg

#endif