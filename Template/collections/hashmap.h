#pragma once

#include "collections/vector2d.h"
#include "math/mod/fix.h"

namespace collections {

template<typename K, typename V>
struct Hashmap {
  inline Hashmap() {}

  inline Hashmap(int size, int keyCap = -1) {
    init(size, keyCap);
  }

  inline void init(int size, int keyCap = -1) {
    _vs.init(size, keyCap);
  }

  inline void set(K key, V value, bool forceEmplaceBack = false) {
    int idx = math::fixMod<K>(key, _vs._n);
    if (forceEmplaceBack) {
      _vs.emplaceBack(idx, key, value);
      return;
    }
    int edgeIdx = _getEdgeIdx(idx, key);
    if (edgeIdx >= 0) {
      _vs.values[edgeIdx].second = value;
    } else {
      _vs.emplaceBack(idx, key, value);
    }
  }

  inline const V* getPtr(K key) const {
    int edgeIdx = _getEdgeIdx(math::fixMod<K>(key, _vs._n), key);
    return edgeIdx >= 0 ? &_vs.values[edgeIdx].second : nullptr;
  }

  inline int _getEdgeIdx(int idx, K key) const {
    for (int edgeIdx = _vs.lastOut[idx]; edgeIdx >= 0;
         edgeIdx = _vs.nxtOut[edgeIdx]) {
      if (_vs.values[edgeIdx].first == key) {
        return edgeIdx;
      }
    }
    return -1;
  }

  Vector2D<pair<K, V>> _vs;
};

} // namespace collections
