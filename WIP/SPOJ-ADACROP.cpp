// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_TREAP_CALC_PREFIX_RETURN
// #define BASE_TREAP_ERASE
#define BASE_TREAP_RESERVE
#define BASE_TREAP_UPDATE
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/base_treap.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 200000;
const int MAXQ = MAXN;
const int MAXNQ = MAXN + MAXQ;

namespace ds {

template<typename KEY = int>
struct TreapSize : BaseTreap<int, int, KEY> {
  inline void _initRangeV(int& res) override {
    res = 0;
  }

  inline void _initV(typename TreapSize::_Node& node) override {
    node._v = node._rangeV = 0;
  }

  inline void _updateV(typename TreapSize::_Node& node, const int& delta) override {
    bool wasValid = node._v;
    node._v += delta;
    if (wasValid ^ CAST<bool>(node._v)) {
      if (wasValid) {
        --node._rangeV;
      } else {
        ++node._rangeV;
      }
    }
  }

  inline void _mergeRangeV(typename TreapSize::_Node& node) override {
    node._rangeV = (node._lIdx < 0 ? 0 : this->_nodes[node._lIdx]._rangeV) + (node._v > 0) +
                   (node._rIdx < 0 ? 0 : this->_nodes[node._rIdx]._rangeV);
  }

  inline void _appendNode(int& res, const typename TreapSize::_Node& node) override {
    if (node._v > 0) {
      ++res;
    }
  }

  inline void _appendRange(int& res, const typename TreapSize::_Node& node) override {
    res += node._rangeV;
  }
};

} // namespace ds

ds::TreapSize<int> treaps[MAXNQ];
int as[MAXN], qIdx[MAXQ], qA[MAXQ];
int cnts[MAXNQ];

int main() {
  int n, q;
  io::readInt(n);
  io::readInt(q);
  vector<int> dis;
  dis.reserve(n + q);
  FOR(i, 0, n) {
    io::readInt(as[i]);
    dis.push_back(as[i]);
  }
  FOR(i, 0, q) {
    io::readInt(qIdx[i]);
    io::readInt(qA[i]);
    dis.push_back(qA[i]);
  }
  SORTUNIQUE(dis);
  FOR(i, 0, n) {
    as[i] = INDEX(dis, as[i]);
    ++cnts[as[i]];
    treaps[as[i]].update(i, 1);
  }
  FOR(i, 0, q) {
    qA[i] = INDEX(dis, qA[i]);
    ++cnts[qA[i]];
  }
  FORSIZE(i, dis) {
    treaps[i].reserve(cnts[i]);
  }
  FOR(i, 0, q) {
    int idx = qIdx[i];
    int a = qA[i];
    auto& treap = treaps[a];
    io::writeInt(treap.calcPrefix(idx - 1));
    io::writeChar('\n');
    if (as[idx] == a) {
      continue;
    }
    treap.update(idx, 1);
    treaps[as[idx]].update(idx, -1);
    as[idx] = a;
  }
}
