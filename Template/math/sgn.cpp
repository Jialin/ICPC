// @autogen
namespace math {

template<typename T>
inline int sgn(T a, T b) {
  return a < b ? -1 : a == b ? 0 : 1;
}

} // namespace math