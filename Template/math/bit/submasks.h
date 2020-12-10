#pragma once

using namespace std;

namespace math {

// Computes the n-th gray code
template<typename V = int>
inline void submasks(V mask, const function<bool(int)>& processor) {
  if (!processor(0)) {
    return;
  }
  for (int submask = mask; submask; submask = (submask - 1) & mask) {
    if (!processor(submask)) {
      return;
    }
  }
}

} // namespace math