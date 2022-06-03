// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"
#define MANACHER_EVEN_LOWER
#define MANACHER_EVEN_UPPER
#define MANACHER_ODD_LOWER
#define MANACHER_ODD_UPPER
#define MANACHER_RESERVE
#include "string/palindrome/manacher_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"
#include "string/palindrome/manacher.h"

// Last include
#include "debug/debug.h"

const int MAXL = 100000 + 10;

int n, bound;
char s[MAXL];
int status;

inline int countPalidrome(int size) {
  return (size <= bound ? size * (size + 1) : bound * ((size << 1) - bound + 1)) >> 1;
}

inline int countCrossPal(int lower, int upper, int gap) {
  int delta = (max(upper - lower - bound, 0) + 1) >> 1;
  lower += delta;
  upper -= delta;
  return max(min(gap - lower, upper - gap), 0);
}

str::Manacher man;

inline int calcCrossPal(int lower, int upper, int gap) {
  int subSize = upper - lower, leftSize = gap - lower;
  man._calc(subSize, s + lower, ((subSize << 1) | 1) - max((upper - gap) >> 1, 0));
  int res = 0;
  FOR(i, 0, subSize) {
    res += countCrossPal(man.oddLower(i), man.oddUpper(i), leftSize) +
           countCrossPal(man.evenLower(i), man.evenUpper(i), leftSize);
  }
  return res;
}

struct PalindromeTreeV {
  int cnt, crossCnt;
  bool crossSame;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const PalindromeTreeV& v) {
    return o << tostring2("cnt", v.cnt, "crossCnt", v.crossCnt, "crossSame", v.crossSame);
  }
#endif
};

int Q_LOWER, Q_UPPER;

struct PalindromeTree : ds::BaseLazyCompactSegmentTree<PalindromeTreeV, nullptr_t, char, int> {
  using V = PalindromeTreeV;
  using InitV = nullptr_t;
  using Update = char;
  using TraverseArgs = int;
  using Node = typename PalindromeTree::_Node;

  inline int getCnt(const Node& node) {
    return node.v.cnt + node.v.crossCnt;
  }

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
  inline Traverse _traverse(Node& node, int lower, int upper, TraverseArgs& args) override {
    if (lower <= node.lower && node.upper <= upper) {
      args += getCnt(node);
      return Traverse::NONE;
    }
    int medium = (node.lower + node.upper) >> 1;
    if (upper <= medium) {
      return Traverse::LEFT;
    }
    if (medium <= lower) {
      return Traverse::RIGHT;
    }
    int oldLower = max(medium - bound, node.lower), oldUpper = min(medium + bound, node.upper);
    int newLower = max(oldLower, lower), newUpper = min(oldUpper, upper);
    if (oldLower == newLower && oldUpper == newUpper) {
      args += node.v.crossCnt;
    } else if (node.v.crossSame) {
      assert(newLower <= medium && medium <= newUpper);
      args += countPalidrome(newUpper - newLower) - countPalidrome(medium - newLower) -
              countPalidrome(newUpper - medium);
    } else {
      args += calcCrossPal(newLower, newUpper, medium);
    }
    return Traverse::ALL;
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update != ' ';
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    bool wasUpdated = node.update != ' ';
    int medium = (node.lower + node.upper) >> 1;
    auto& v = node.v;
    node.update = update;
    if (!wasUpdated) {
      v.cnt = countPalidrome(medium - node.lower) + countPalidrome(node.upper - medium);
      v.crossCnt = countPalidrome(node.upper - node.lower) - v.cnt;
      v.crossSame = true;
    }
    if (medium - node.lower < (bound << 1)) {
      FOR(i, node.lower, medium) {
        s[i] = update;
      }
    } else {
      FORR(i, node.lower + bound - 1, node.lower) {
        s[i] = update;
      }
      FOR(i, medium - bound, medium) {
        s[i] = update;
      }
    }
    if (node.upper - medium < (bound << 1)) {
      FOR(i, medium, node.upper) {
        s[i] = update;
      }
    } else {
      FORR(i, medium + bound - 1, medium) {
        s[i] = update;
      }
      FOR(i, node.upper - bound, node.upper) {
        s[i] = update;
      }
    }
  }

  inline void _clearUpdate(Node& node) override {
    node.update = ' ';
  }

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.cnt = 1;
    v.crossCnt = 0;
    v.crossSame = false;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    if (status == 1) {
      if (Q_UPPER <= rNode.lower - bound || rNode.lower + bound <= Q_LOWER) {
        res.cnt = getCnt(lNode) + getCnt(rNode);
        return;
      }
      int lower = max(rNode.lower - bound, lNode.lower);
      int upper = min(rNode.upper, rNode.lower + bound);
      res.crossSame = Q_LOWER <= lower && upper <= Q_UPPER;
      if (res.crossSame) {
        res.cnt = getCnt(lNode) + getCnt(rNode);
        res.crossCnt = countPalidrome(upper - lower) - countPalidrome(rNode.lower - lower) -
                       countPalidrome(upper - rNode.lower);
        return;
      }
    }
    if (status == 2) {
      return;
    }
    res.cnt = getCnt(lNode) + getCnt(rNode);
    int lower = max(rNode.lower - bound, lNode.lower);
    int upper = min(rNode.upper, rNode.lower + bound);
    if (!status) {
      res.crossSame = false;
    }
    if (res.crossSame) {
      res.crossCnt = countPalidrome(upper - lower) - countPalidrome(rNode.lower - lower) -
                     countPalidrome(upper - rNode.lower);
    } else {
      res.crossCnt = calcCrossPal(lower, upper, rNode.lower);
    }
  }
};

char cs[2];

int main() {
  n = io::readCharArray(s);
  io::readInt(bound);
  man.reserve(bound << 1);
  int q;
  io::readInt(q);
  PalindromeTree st;
  status = 0;
  Q_LOWER = 0;
  Q_UPPER = n;
  st.init(vector<nullptr_t>(n));
  FOR(_, 0, q) {
    int op;
    io::readInt(op);
    io::readInt(Q_LOWER);
    io::readInt(Q_UPPER);
    --Q_LOWER;
    if (op == 1) {
      status = 1;
      io::readCharArray(cs);
      st.updateRange(Q_LOWER, Q_UPPER, cs[0]);
    } else {
      status = 2;
      int res = 0;
      st.traverse(Q_LOWER, Q_UPPER, res);
      io::writeInt(res, '\n');
    }
  }
  return 0;
}
