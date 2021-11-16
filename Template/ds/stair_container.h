// !macro_gen
// ALL STAIR_CONTAINER_ALL
#pragma once

using namespace std;

namespace ds {

// Maintains descendent stair
//
// y
// ^
// |
// --+
// | |
// | +---+
// |     |
// +-----|--> x
template<typename V>
struct StairContainer {
#ifdef STAIR_CONTAINER_CLEAR // ^
  inline void clear() {
    _vs.clear();
  }
#endif

#ifdef STAIR_CONTAINER_IS_FULLY_INSIDE // ^
  // Checks whether the point it's fully inside the stage
  inline bool isFullyInside(const V& x, const V& y) const {
    auto it = _vs.upper_bound(x);
    return it != _vs.end() && y < it->second;
  }
#endif

#ifdef STAIR_CONTAINER_UPDATE // ^
  inline bool update(const V& x, const V& y) {
    auto it = _vs.lower_bound(x);
    if (it != _vs.end() && y <= it->second) {
      return false;
    }
    if (it != _vs.end() && it->first == x) {
      it->second = y;
    } else {
      it = _vs.emplace(x, y).first;
    }
    if (it == _vs.begin()) {
      return true;
    }
    for (--it; it->second < y;) {
      if (it == _vs.begin()) {
        _vs.erase(it);
        break;
      } else {
        _vs.erase(it--);
      }
    }
    return true;
  }
#endif

  map<V, V> _vs;
};

} // namespace ds
