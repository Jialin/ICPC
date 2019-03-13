#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

#define SIZE(v) (static_cast<int>((v).size()))

#define FOR(i,l,r) for(int i=(l);i<(r);++i)

namespace tree { namespace trie {

template<int MAXL>
class Trie {
  int letterCnt;
  vector<int> children[MAXL];

  inline int createNode() {
    for (int i = 0; i < letterCnt; ++i) children[i].push_back(-1);
    return nodeCnt++;
  }

public:
  static const int ROOT = 0;
  int nodeCnt;

  // Initializes the trie with letter count
  inline void init(int _letterCnt) {
    letterCnt = _letterCnt;
    for (int i = 0; i < letterCnt; ++i) children[i].clear();
    nodeCnt = 0;
    createNode();
  }

  // Accesses the child and creates node when necessary
  inline int forceAccess(int idx, int letter) {
    int res = children[letter][idx];
    if (res < 0) res = createNode();
    return children[letter][idx] = res;
  }

  // Accesses the child
  inline int access(int idx, int letter) {
    return children[letter][idx];
  }
}; // class Trie
}} // namespace tree::trie

const int MAXBIT = 19;

tree::trie::Trie<2> trie;
vector<int> cnt;

inline int calcCnt(int idx, int letter) {
  idx = trie.access(idx, letter);
  return idx < 0 ? 0 : cnt[idx];
}

inline void add(int v) {
  int idx = 0;
  for (int j = MAXBIT; j >= 0 && idx >= 0; --j) {
    idx = trie.forceAccess(idx, (v >> j) & 1);
    if (idx < SIZE(cnt)) {
      ++cnt[idx];
    } else {
      cnt.push_back(1);
    }
  }
}

int main() {
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    trie.init(2);
    int n, k; scanf("%d%d", &n, &k);
    cnt.clear();
    cnt.resize(1, 0);
    int xorSum = 0;
    add(xorSum);
    long long res = 0;
    FOR(i, 0, n) {
      int a; scanf("%d", &a); xorSum ^= a;
      int idx = 0;
      for (int j = MAXBIT; j >= 0 && idx >= 0; --j) {
        int xorBit = (xorSum >> j) & 1;
        if (k & (1 << j)) {
          res += calcCnt(idx, xorBit);
          idx = trie.access(idx, xorBit ^ 1);
        } else {
          idx = trie.access(idx, xorBit);
        }
      }
      add(xorSum);
    }
    printf("%lld\n", res);
  }
  return 0;
}

