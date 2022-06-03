// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_COMPACT_SEGMENT_TREE_INIT
#define _BASE_COMPACT_SEGMENT_TREE_CALC_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
#include "ds/segment_tree/base_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct CompactSegmentTreeBracketV {
  int res, openCnt, closeCnt;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const CompactSegmentTreeBracketV& v) {
    o << '{' << tostring2("res", v.res, "openCnt", v.openCnt, "closeCnt", v.closeCnt) << '}';
    return o;
  }
#endif
};

const int MAXN = 1000000 + 1;

char s[MAXN];

struct CompactSegmentTreeBracket
    : ds::BaseCompactSegmentTree<CompactSegmentTreeBracketV, nullptr_t> {
  using V = CompactSegmentTreeBracketV;
  using InitV = nullptr_t;
#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  using Update = int;
#endif
  using Node = CompactSegmentTreeBracket::_Node;

#ifdef _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.res = res.openCnt = 0;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    auto& v = node.v;
    int matchCnt = min(res.openCnt, v.closeCnt);
    res.res += v.res + (matchCnt << 1);
    res.openCnt += v.openCnt - matchCnt;
  }
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_UPDATE_V
  inline void _updateV(const Update& update, Node& node) override {
    assert(false);
  }
#endif

  inline void _initV(InitV initV, Node& node) override {
    auto& v = node.v;
    v.res = 0;
    if (s[node.lower] == '(') {
      v.openCnt = 1;
      v.closeCnt = 0;
    } else {
      v.openCnt = 0;
      v.closeCnt = 1;
    }
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    int matchCnt = min(lv.openCnt, rv.closeCnt);
    res.res = lv.res + rv.res + (matchCnt << 1);
    res.openCnt = lv.openCnt + rv.openCnt - matchCnt;
    res.closeCnt = lv.closeCnt + rv.closeCnt - matchCnt;
  }
};

int main() {
  int n = io::readCharArray(s);
  CompactSegmentTreeBracket st;
  st.init(vector<nullptr_t>(n));
  int q;
  io::readInt(q);
  CompactSegmentTreeBracketV res;
  FOR(_, 0, q) {
    int lower, upper;
    io::readInt(lower);
    io::readInt(upper);
    st._clearV(res);
    st._calcRange(0, lower - 1, upper, res);
    io::writeInt(res.res, '\n');
  }
  return 0;
}
