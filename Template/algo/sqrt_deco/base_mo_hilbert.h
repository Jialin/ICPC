// !macro_gen
// ALL BASE_MO_HILBERT_ALL
#pragma once

#include "algo/sqrt_deco/base_mo_hilbert_macros.h"

#include "debug/debug_basic.h"
#include "math/fractal/hilbert_order.h"

namespace algo {

struct MoHilbertQuery {
  int lower, upper, idx;
  int64_t order;

  inline MoHilbertQuery(int lower, int upper, int idx) : lower(lower), upper(upper), idx(idx) {}

  inline int dist(const MoHilbertQuery& o) const {
    return abs(lower - o.lower) + abs(upper - o.upper);
  }

  inline bool operator<(const MoHilbertQuery& o) const {
    return order < o.order;
  }
};

struct BaseMoHilbertState {
  virtual inline void _clear() = 0;
  virtual inline void _initEmptyRange() = 0;
  virtual inline void _pushBack(int idx) = 0;
  virtual inline void _pushFront(int idx) = 0;
  virtual inline void _popBack(int idx) = 0;
  virtual inline void _popFront(int idx) = 0;
  virtual inline void _handleQuery(const MoHilbertQuery& query) = 0;

  inline void _handle(const MoHilbertQuery& query) {
    if (upper <= query.lower || query.upper <= lower) {
      _clear();
      lower = upper = query.lower;
      _initEmptyRange();
      for (; upper < query.upper; _pushBack(upper++)) {}
    } else {
      for (; lower < query.lower; _popFront(lower++)) {}
      for (; query.upper < upper; _popBack(--upper)) {}
      for (; query.lower < lower; _pushFront(--lower)) {}
      for (; upper < query.upper; _pushBack(upper++)) {}
    }
    _handleQuery(query);
  }

  int lower, upper;
};

template<typename STATE, int RANGE_BIT>
struct MoHilbert {
#ifdef BASE_MO_HILBERT_RESERVE // ^
  inline void reserve(int n) {
    _queries.reserve(n);
  }
#endif

#ifdef BASE_MO_HILBERT_CLEAR // ^
  inline void clear() {
    _queries.clear();
  }
#endif

  inline void addQuery(int lower, int upper, int idx) {
    DEBUG_TRUE((is_base_of<BaseMoHilbertState, STATE>::value))
    _queries.emplace_back(lower, upper, idx);
    DEBUG_LE(upper, 1 << RANGE_BIT)
    _queries.back().order = math::hilbertOrder(RANGE_BIT, lower, upper);
  }

#ifdef BASE_MO_HILBERT_HANDLE // ^
  inline void handle() {
    STATE state;
    // BASE_MO_HILBERT_HANDLE => _BASE_MO_HILBERT_HANDLE
    _handle(state);
  }
#endif

#ifdef _BASE_MO_HILBERT_HANDLE // ^
  inline void _handle(STATE& state) {
    if (_queries.empty()) {
      return;
    }
    SORT(_queries);
    _bubbleSort();
    state.lower = state.upper = _queries[0].lower;
    state._initEmptyRange();
    for (const auto& query : _queries) {
      state._handle(query);
    }
  }
#endif

  inline void _bubbleSort() {
    int bound = SIZE(_queries) - 1;
    FOR(i, 2, bound) {
      for (int j = i; j >= 2; --j) {
        if (_queries[i - 2].dist(_queries[i - 1]) + _queries[i].dist(_queries[i + 1]) >
            _queries[i - 2].dist(_queries[i]) + _queries[i - 1].dist(_queries[i + 1])) {
          swap(_queries[i - 1], _queries[i]);
        } else {
          break;
        }
      }
    }
  }

  vector<MoHilbertQuery> _queries;
};

} // namespace algo
