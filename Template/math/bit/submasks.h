#pragma once

using namespace std;

namespace math {

// Computes the n-th gray code
template<typename V = int>
inline void submasks(V mask, const function<void(int)>& processor) {
  processor(0);
  for (int submask = mask; submask; submask = (submask - 1) & mask) {
    processor(submask);
  }
}

} // namespace math