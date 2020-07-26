#pragma once

#include <vector>

using namespace std;

namespace collections {

class Bitset {
public:
  inline Bitset(int n, bool zero = true) {
    init(n, zero);
  }

  inline void init(int n, bool zero = true) {
    n_ = n;
    data_.assign((n + 31) >> 5, zero ? 0 : 4294967295);
  }

  inline void set(int pos, bool v = true) {
    if (v) {
      data_[pos >> 5] |= 1U << (pos & 31);
    } else {
      data_[pos >> 5] &= ~(1U << (pos & 31));
    }
  }

  inline bool test(int pos) {
    return data_[pos >> 5] & (1U << (pos & 31));
  }

private:
  int n_;
  vector<unsigned int> data_;
};

} // namespace collections
