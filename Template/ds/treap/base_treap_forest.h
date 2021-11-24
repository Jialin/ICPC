// !macro_gen
// ALL BASE_TREAP_FOREST_ALL
#pragma once

#include "ds/treap/base_treap_macros.h" // INCLUDE

#include "common/macros.h"
#include "debug/debug_basic.h"
#include "ds/treap/base_treap.h"

using namespace std;

namespace ds {

template<typename NODE_V, typename RANGE_V = NODE_V, typename KEY = int>
struct BaseTreapForest : BaseTreap<NODE_V, RANGE_V, KEY> {
  inline void init(int rootCnt) {
    this->_rootCnt = rootCnt;
    this->clear();
  }

#ifdef BASE_TREAP_FOREST_RESERVE_ROOTS // ^
  inline void reserveRoots(int n) {
    this->_roots.reserve(n);
  }
#endif

#ifdef BASE_TREAP_FOREST_INIT_ORDERED_ITEMS // ^
  inline void initOrderedItems(const vector<pair<KEY, NODE_V>>& vs, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    // BASE_TREAP_FOREST_INIT_ITEMS => _BASE_TREAP_INIT_ORDERED_ITEMS
    this->_roots[rootIdx] = this->_initOrderedItems(vs, 0, SIZE(vs));
  }
#endif

#ifdef BASE_TREAP_FOREST_UPDATE // ^
  inline void update(const KEY& key, const NODE_V& delta, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    // BASE_TREAP_FOREST_UPDATE => _BASE_TREAP_UPDATE
    this->_roots[rootIdx] = this->_update(this->_roots[rootIdx], key, delta);
  }
#endif

#ifdef BASE_TREAP_FOREST_ERASE // ^
  inline void erase(const KEY& key, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    // BASE_TREAP_FOREST_ERASE => _BASE_TREAP_ERASE
    this->_roots[rootIdx] = this->_erase(this->_roots[rootIdx], key);
  }
#endif

#ifdef BASE_TREAP_FOREST_CALC_PREFIX // ^
  // Calculates prefix from [-inf, upper1]. NOTE: <upper1> is included
  inline RANGE_V calcPrefix(const KEY& upper1, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    RANGE_V res;
    this->_initRangeV(res);
    // BASE_TREAP_FOREST_CALC_PREFIX => _BASE_TREAP_CALC_PREFIX
    this->_calcPrefix(this->_roots[rootIdx], upper1, res);
    return res;
  }
#endif

#ifdef BASE_TREAP_FOREST_CALC_SUFFIX // ^
  inline RANGE_V calcSuffix(const KEY& lower, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    RANGE_V res;
    this->_initRangeV(res);
    // BASE_TREAP_FOREST_CALC_SUFFIX => _BASE_TREAP_CALC_SUFFIX
    this->_calcSuffix(this->_roots[rootIdx], lower, res);
    return res;
  }
#endif

#ifdef BASE_TREAP_FOREST_CALC_RANGE // ^
  inline RANGE_V calcRange(const KEY& lower, const KEY& upper, int rootIdx) {
    DEBUG_LT(rootIdx, SIZE(this->_roots));
    RANGE_V res;
    _initRangeV(res);
    // BASE_TREAP_FOREST_CALC_RANGE => _BASE_TREAP_CALC_RANGE
    _calcRange(this->_roots[rootIdx], lower, upper, res);
    return res;
  }
#endif
};

} // namespace ds
