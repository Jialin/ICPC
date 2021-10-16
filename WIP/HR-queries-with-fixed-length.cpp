// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_int.h"
#include "io/write_char.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

namespace ds {

template<typename V>
struct BaseSlidingWindow {
  virtual bool cmp(const V& append, const V& last) const = 0;

  inline void reserve(int addCount) {
    _vs.reserve(addCount);
  }

  inline void init(int windowSize) {
    _delta = windowSize - 1;
    _startPnt = 0;
    _vs.clear();
  }

  inline void add(int idx, V v) {
    for (; _startPnt < SIZE(_vs) && cmp(v, _vs.back().second); _vs.pop_back()) {}
    for (; _startPnt < SIZE(_vs) && idx - _vs[_startPnt].first > _delta; ++_startPnt) {}
    _vs.emplace_back(idx, std::move(v));
  }

  inline const pair<int, V>& get() const {
    return _vs[_startPnt];
  }

  int _delta, _startPnt;
  vector<pair<int, V>> _vs;
};

} // namespace ds

namespace ds {

template<typename V>
struct SlidingWindowMax : BaseSlidingWindow<V> {
  bool cmp(const V& append, const V& last) const override {
    return append >= last;
  }
};

} // namespace ds

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> vs(n);
  FOR(i, 0, n) {
    io::readInt(vs[i]);
  }
  ds::SlidingWindowMax<int> sw;
  FOR(_, 0, q) {
    int ws;
    io::readInt(ws);
    sw.init(ws);
    FOR(i, 0, ws - 1) {
      sw.add(i, vs[i]);
    }
    int res = 1000000;
    FOR(i, ws - 1, n) {
      sw.add(i, vs[i]);
      res = min(res, sw.get().second);
    }
    io::writeInt(res);
    io::writeChar('\n');
  }
}
