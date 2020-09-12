#pragma once

#include "collections/vector2d.h"
#include "math/mod/fix.h"

namespace collections {

template<typename T>
struct Hashset {
  inline Hashset() {}

  inline Hashset(int size, int valueCap = -1) {
    init(size, valueCap);
  }

  inline void init(int size, int valueCap = -1) {
    _vs.init(size, valueCap);
  }

  inline void add(T v, bool forceAdd = false) {
    int idx = math::fixMod<T>(v, _vs._n);
    if (forceAdd || !contains(v)) {
      _vs.add(idx, v);
    }
  }

  inline bool contains(T v) const {
    int idx = math::fixMod<T>(v, _vs._n);
    for (int edgeIdx = _vs.lastOut[idx]; edgeIdx >= 0;
         edgeIdx = _vs.nxtOut[edgeIdx]) {
      if (_vs.values[edgeIdx] == v) {
        return true;
      }
    }
    return false;
  }

  Vector2D<T> _vs;
};

} // namespace collections
