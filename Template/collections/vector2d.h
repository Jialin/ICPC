#pragma once

#include <vector>

using namespace std;

namespace collections {

template<typename T>
struct Vector2D {
  inline Vector2D() {}

  inline Vector2D(int n, int valueCap = -1) {
    init(n, valueCap);
  }

  inline void init(int n, int valueCap = -1) {
    _n = n;
    lastOut.assign(n, -1);
    nxtOut.clear();
    values.clear();
    if (valueCap > 0) {
      nxtOut.reserve(valueCap);
      values.reserve(valueCap);
    }
    _edgeIdx = 0;
  }

  inline void add(int x, T v) {
    nxtOut.push_back(lastOut[x]);
    lastOut[x] = _edgeIdx++;
    values.push_back(v);
  }

  vector<int> lastOut, nxtOut;
  vector<T> values;
  int _n, _edgeIdx;
};

} // namespace collections
