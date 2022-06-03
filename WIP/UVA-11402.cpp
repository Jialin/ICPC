// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_CALC_RANGE
#define BASE_LAZY_COMPACT_SEGMENT_TREE_INIT
#define BASE_LAZY_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/base_lazy_compact_segment_tree.h"
#include "io/read_char_array.h"
#include "io/read_int.h"
#include "io/write_char_array.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

struct PrirateCnts : ds::BaseLazyCompactSegmentTree<pair<int, int>, pair<int, int>, char> {
  using V = pair<int, int>;
  using InitV = pair<int, int>;
  using Update = char;
  using Node = typename PrirateCnts::_Node;

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_CLEAR_V
  inline void _clearV(V& res) override {
    res.first = 0;
  }
#endif

#ifdef _BASE_LAZY_COMPACT_SEGMENT_TREE_APPEND_V
  inline void _appendV(const Node& node, V& res) override {
    res.first += node.v.first;
  }
#endif

  inline bool _hasUpdate(Node& node) override {
    return node.update;
  }

  inline void _applyUpdate(const Update& update, Node& node) override {
    if (update == 'F') {
      node.update = update;
      node.v.first = node.v.second;
    } else if (update == 'E') {
      node.update = update;
      node.v.first = 0;
    } else if (update == 'I') {
      if (node.update == 'I') {
        node.update = ' ';
      } else if (node.update == ' ') {
        node.update = 'I';
      } else {
        node.update ^= 'E' ^ 'F';
      }
      node.v.first = node.v.second - node.v.first;
    }
  }

  inline void _clearUpdate(Node& node) override {
    node.update = ' ';
  }

  inline void _initV(InitV initV, Node& node) override {
    node.v = initV;
  }

  inline void _mergeV(const Node& lNode, const Node& rNode, V& res) override {
    const auto &lv = lNode.v, rv = rNode.v;
    res.first = lv.first + rv.first;
    res.second = lv.second + rv.second;
  }
};

const int MAXPART = 100;
const int MAXL = 50 + 1;
const int MAXQ = 1000 + 3;

vector<pair<string, int>> parts;
char part[MAXL];
vector<int> bounds;
vector<tuple<char, int, int>> queries;
vector<pair<int, int>> cnts;

int main() {
  parts.reserve(MAXPART);
  bounds.reserve(MAXQ << 1);
  queries.reserve(MAXQ);
  cnts.reserve(MAXQ << 1);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; ++taskIdx) {
    int n, m = 0;
    io::readInt(n);
    parts.clear();
    FOR(_, 0, n) {
      int cnt;
      io::readInt(cnt);
      io::readCharArray(part);
      parts.emplace_back(part, cnt);
      m += cnt * parts.back().first.size();
    }
    int q;
    io::readInt(q);
    queries.clear();
    bounds.clear();
    bounds.push_back(0);
    bounds.push_back(m);
    FOR(_, 0, q) {
      int lower, upper;
      io::readCharArray(part);
      io::readInt(lower);
      io::readInt(upper);
      ++upper;
      queries.emplace_back(part[0], lower, upper);
      bounds.push_back(lower);
      bounds.push_back(upper);
    }
    SORTUNIQUE(bounds);
    int boundCnt = SIZE(bounds) - 1;
    cnts.assign(boundCnt, {0, 0});
    FOR(i, 0, boundCnt) {
      cnts[i].second = bounds[i + 1] - bounds[i];
    }
    int boundIdx = 0, idx = 0;
    for (const auto& [part, _remainCnt] : parts) {
      int oneCnt = count(ALL(part), '1');
      int remainCnt = _remainCnt, partIdx = 0;
      while (remainCnt) {
        bool oneStep = partIdx;
        int jumpCnt;
        if (!partIdx) {
          jumpCnt = min((bounds[boundIdx + 1] - idx) / SIZE(part), remainCnt);
          oneStep = !jumpCnt;
        }
        if (oneStep) {
          if (part[partIdx++] == '1') {
            ++cnts[boundIdx].first;
          }
          if (partIdx == part.size()) {
            partIdx = 0;
            --remainCnt;
          }
          ++idx;
        } else {
          idx += SIZE(part) * jumpCnt;
          cnts[boundIdx].first += oneCnt * jumpCnt;
          remainCnt -= jumpCnt;
        }
        if (idx == bounds[boundIdx + 1]) {
          ++boundIdx;
        }
      }
    }
    io::writeCharArray("Case ");
    io::writeInt(taskIdx, ':');
    io::writeChar('\n');
    int sCnt = 0;
    PrirateCnts st;
    st.init(move(cnts));
    for (auto [op, lower, upper] : queries) {
      lower = INDEX(bounds, lower);
      upper = INDEX(bounds, upper);
      if (op == 'S') {
        io::writeChar('Q');
        io::writeInt(++sCnt, ':');
        io::writeChar(' ');
        io::writeInt(st.calcRange(lower, upper), '\n');
      } else {
        st.updateRange(lower, upper, op);
      }
    }
  }
  return 0;
}
