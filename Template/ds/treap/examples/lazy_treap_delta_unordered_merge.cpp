// CF-702-F: https://codeforces.com/contest/702/problem/F
// - Merge unordered treap
// - Apply _key change within a range

// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define BASE_LAZY_TREAP_INSERT_RIGHTMOST
#define BASE_LAZY_TREAP_PUSH_ALL
#define BASE_LAZY_TREAP_RESERVE_NODES
#define _BASE_LAZY_TREAP_CALC_LEFTMOST
#define _BASE_LAZY_TREAP_CALC_RIGHTMOST
#define _BASE_LAZY_TREAP_ERASE_LEFTMOST
#define _BASE_LAZY_TREAP_HEAPIFY
#define _BASE_LAZY_TREAP_INSERT_NODE
#define _BASE_LAZY_TREAP_MERGE
#define _BASE_LAZY_TREAP_SPLIT
#include "ds/treap/base_lazy_treap_macros.h"

#include "ds/treap/base_lazy_treap.h"
#include "io/read_int.h"
#include "io/write_int.h"

// Last include
#include "debug/debug.h"

vector<int> results;

struct LazyTreapCustomerNode {
  int cnt;
  vector<int> idxs;

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const LazyTreapCustomerNode& node) {
    o << "(cnt:" << node.cnt << " idxs:" << tostring(node.idxs) << ')';
    return o;
  }
#endif
};

struct LazyTreapCustomerUpdate {
  int deltaMoney, cnt;

  inline void init() {
    deltaMoney = 0;
    cnt = 0;
  }

#ifdef LOCAL
  inline friend ostream& operator<<(ostream& o, const LazyTreapCustomerUpdate& update) {
    o << "(deltaMoney:" << update.deltaMoney << " cnt:" << update.cnt << ')';
    return o;
  }
#endif
};

bool initMode;

struct LazyTreapCustomer
    : ds::BaseLazyTreap<LazyTreapCustomerNode, LazyTreapCustomerUpdate, nullptr_t, int> {
  using NodeV = LazyTreapCustomerNode;
  using UpdateV = LazyTreapCustomerUpdate;
  using RangeV = nullptr_t;
  using Node = typename LazyTreapCustomer::_Node;

  inline void _initRangeV(RangeV& rangeV) override {}

  inline void _initAllVs(Node& node, const NodeV& nodeV) override {
    if (initMode) {
      node._v = nodeV;
      node._updateV.init();
    } else {
      auto& curNodeV = node._v;
      int deltaCnt = nodeV.cnt - curNodeV.cnt;
      for (int idx : nodeV.idxs) {
        results[idx] += deltaCnt;
      }
      curNodeV.idxs.insert(curNodeV.idxs.end(), nodeV.idxs.begin(), nodeV.idxs.end());
    }
  }

  inline void _pushUpdate(UpdateV& updateV, const UpdateV& srcUpdateV) override {
    updateV.deltaMoney += srcUpdateV.deltaMoney;
    updateV.cnt += srcUpdateV.cnt;
  }

  inline void _mergeRangeV(_Node& node) override {}

  inline void _pushAndClearUpdate(_Node& node) override {
    auto& updateV = node._updateV;
    if (!updateV.cnt) {
      return;
    }
    if (node._lIdx >= 0) {
      _pushUpdate(_nodes[node._lIdx]._updateV, updateV);
    }
    if (node._rIdx >= 0) {
      _pushUpdate(_nodes[node._rIdx]._updateV, updateV);
    }
    node._key += updateV.deltaMoney;
    node._v.cnt += updateV.cnt;
    updateV.init();
  }
};

LazyTreapCustomer treap;
LazyTreapCustomerNode globalNode;
LazyTreapCustomerUpdate globalUpdate;

inline void dfs(int idx) {
  if (idx < 0) {
    return;
  }
  auto& node = treap._nodes[idx];
  treap._pushAndClearUpdate(node);
  dfs(node._lIdx);
  dfs(node._rIdx);
  treap._mergeV(node);
  for (int idx : node._v.idxs) {
    results[idx] += node._v.cnt;
  }
}

int main() {
  int n;
  io::readInt(n);
  vector<pair<int, int>> tshirts;
  tshirts.reserve(n);
  FOR(i, 0, n) {
    int c, q;
    io::readInt(c);
    io::readInt(q);
    tshirts.emplace_back(q, c);
  }
  sort(ALL(tshirts), [](const auto& x, const auto& y) {
    return x.first > y.first || (x.first == y.first && x.second < y.second);
  });
  int q;
  io::readInt(q);
  vector<pair<int, int>> queries;
  queries.reserve(q);
  FOR(i, 0, q) {
    int v;
    io::readInt(v);
    queries.emplace_back(v, i);
  }
  sort(queries.begin(), queries.end());
  initMode = true;
  treap.reserveNodes(q);
  globalNode.cnt = 0;
  globalNode.idxs.clear();
  FOR(i, 0, q) {
    globalNode.idxs.push_back(queries[i].second);
    if (i + 1 == q || queries[i].first != queries[i + 1].first) {
      treap.insertRightmost(queries[i].first, globalNode);
      globalNode.idxs.clear();
    }
  }
  initMode = false;
  results.resize(q);
  FOR(i, 0, n) {
    int c = tshirts[i].second;
    int lIdx, rIdx;
    treap._split(treap._roots[0], c, lIdx, rIdx);
    if (rIdx >= 0) {
      globalUpdate.deltaMoney = -c;
      globalUpdate.cnt = 1;
      treap._pushUpdate(treap._nodes[rIdx]._updateV, globalUpdate);
    }
    if (lIdx >= 0 && rIdx >= 0) {
      const auto* lMax = treap._calcRightmost(lIdx);
      while (rIdx >= 0) {
        const auto* rMin = treap._calcLeftmost(rIdx);
        if (lMax->_key < rMin->_key) {
          break;
        }
        auto* node = treap._eraseLeftmost(rIdx);
        if (node->_key) {
          lIdx = treap._insertNode(lIdx, node - treap._nodes.data());
        } else {
          for (int idx : node->_v.idxs) {
            results[idx] += node->_v.cnt;
          }
        }
      }
      treap._roots[0] = treap._merge(lIdx, rIdx);
    }
  }
  dfs(treap._roots[0]);
  FOR(i, 0, q) {
    io::writeInt(results[i]);
    io::writeChar(i + 1 == q ? '\n' : ' ');
  }
  return 0;
}
