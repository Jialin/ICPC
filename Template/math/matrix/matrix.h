#pragma once

#include <vector>

using namespace std;

namespace math {

template<typename V = int>
class Matrix {
public:
  inline Matrix() {}

  inline Matrix(int n, int m) {
    init(n, m);
  }

  inline void init(int n, int m) {
    assert(n > 0 && m > 0);
    n_ = n;
    m_ = m;
    vs_.resize(n);
    for (auto& row : vs_) {
      row.assign(m, 0);
    }
  }

  inline int n() const {
    return n_;
  }

  inline int m() const {
    return m_;
  }

  inline const V& at(int i, int j) const {
    assert(i < n_ && j < m_);
    return vs_[i][j];
  }

  inline V& at(int i, int j) {
    assert(i < n_ && j < m_);
    return vs_[i][j];
  }

private:
  int n_, m_;
  vector<vector<V>> vs_;
};

} // namespace math
