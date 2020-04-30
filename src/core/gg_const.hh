#ifndef GG_CONST_HH
#define GG_CONST_HH


#include <iostream>


namespace gg 
{
#ifndef NDEBUG
#  define GG_DEBUG(x) std::cerr << __FILE__ << "::" << __func__  << "() - " << x << std::endl
#else
#  define GG_DEBUG(x) do {} while (0)
#endif
} // gg::


#endif