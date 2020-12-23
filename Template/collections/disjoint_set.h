#pragma once

#include <vector>

using namespace std;

namespace collections {

struct DisjointSet {
  inline DisjointSet(int capacity = -1) {
    if (capacity > 0) {
      init(capacity);
    }
  }

  inline void init(int n) {
    _p.resize(n);
    fill(_p.begin(), _p.end(), -1);
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      if (_p[rootX] > _p[rootY]) {
        swap(rootX, rootY);
      }
      _p[rootX] += _p[rootY];
      _p[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcRoot(int x) {
    int root = x;
    for (; _p[root] >= 0; root = _p[root]) {}
    while (_p[x] >= 0) {
      int tmp = _p[x];
      _p[x] = root;
      x = tmp;
    }
    return root;
  }

  vector<int> _p;
};

} // namespace collections
