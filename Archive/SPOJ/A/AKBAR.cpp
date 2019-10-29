#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define FILL(vs, v) fill(vs.begin(), vs.end(), v)
#define SIZE(vs) static_cast<int>(vs.size())
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ALL(vs) vs.begin(), vs.end()

namespace oi {

template <typename T> void readNum(T &res) {
  int ch;
  while ((ch = getchar()) != EOF && !isdigit(ch) && ch != '+' && ch != '-') {
  }
  bool negative = ch == '-';
  res = isdigit(ch) ? ch - '0' : 0;
  while ((ch = getchar()) != EOF && isdigit(ch)) {
    res = (res << 3) + (res << 1) + (ch ^ 48);
  }
  if (negative) {
    res = -res;
  }
}

} // namespace oi

namespace graphs {

class UnweightedGraphForwardStarSimple {
public:
  inline void init(int n, int m = -1) {
    n_ = n;
    lastOut_.resize(n);
    FILL(lastOut_, -1);
    nxtOut_.clear();
    toIdx_.clear();
    if (m >= 0) {
      nxtOut_.reserve(m);
      toIdx_.reserve(m);
    }
  }

  inline void addDirected(int u, int v) {
    int edgeIdx = SIZE(nxtOut_);
    nxtOut_.push_back(lastOut_[u]);
    toIdx_.push_back(v);
    lastOut_[u] = edgeIdx;
  }

  inline void addUndirected(int u, int v) {
    addDirected(u, v);
    addDirected(v, u);
  }

  inline int n() const { return n_; }
  inline int edgeCnt() const { return SIZE(toIdx_); }
  inline int lastOut(int u) const { return lastOut_[u]; }
  inline int nxtOut(int u) const { return nxtOut_[u]; }
  inline int toIdx(int u) const { return toIdx_[u]; }

private:
  int n_;
  vector<int> lastOut_;
  vector<int> nxtOut_;
  vector<int> toIdx_;
}; // class UnweightedGraphForwardStarSimple

} // namespace graphs

graphs::UnweightedGraphForwardStarSimple graph;
vector<int> labels;

vector<int> bfs, nxtBfs;

bool isValid(int x, int range, int label) {
  if (labels[x] >= 0) {
    return false;
  }
  bfs.clear();
  labels[x] = label;
  bfs.push_back(x);
  FOR(i, 0, range) {
    nxtBfs.clear();
    for (int u : bfs) {
      for (int edgeIdx = graph.lastOut(u); edgeIdx >= 0;
           edgeIdx = graph.nxtOut(edgeIdx)) {
        int v = graph.toIdx(edgeIdx);
        if (labels[v] < 0) {
          labels[v] = label;
          nxtBfs.push_back(v);
        } else if (labels[v] != label) {
          return false;
        }
      }
    }
    bfs.swap(nxtBfs);
  }
  return true;
}

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n, r, m;
    oi::readNum(n);
    oi::readNum(r);
    oi::readNum(m);
    graph.init(n);
    FOR(i, 0, r) {
      int x, y;
      oi::readNum(x);
      oi::readNum(y);
      graph.addUndirected(x - 1, y - 1);
    }
    labels.resize(n);
    FILL(labels, -1);
    bool yes = true;
    FOR(i, 0, m) {
      int x, range;
      oi::readNum(x);
      --x;
      oi::readNum(range);
      if (yes) {
        yes = isValid(x, range, i);
      }
    }
    printf("%s\n",
           yes && all_of(ALL(labels), [](int label) { return label >= 0; })
               ? "Yes"
               : "No");
  }
  return 0;
}
