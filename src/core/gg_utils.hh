#ifndef GG_UTILS_HH
#define GG_UTILS_HH


#include <vector>
#include <algorithm>


namespace gg {
namespace utils
{
/* map (template)
Maps 'x' in range [a, b] to a new range [w, z]. Source:
    https://en.wikipedia.org/wiki/Linear_equation#Two-point_form*/

template <typename TI, typename TO>
TO map(TI x, TI a, TI b, TO w, TO z)
{
    return (((x - a) / (double) (b - a)) * (z - w)) + w;
}


/* -------------------------------------------------------------------------- */

/* eraseIf (template)
Erases things from a vector given a lambda F. */

template <typename T, typename F>
void eraseIf(std::vector<T>& v, F&& f)
{
    v.erase(std::remove_if(v.begin(), v.end(), f), v.end());
}
}} // gg::utils::


#endif