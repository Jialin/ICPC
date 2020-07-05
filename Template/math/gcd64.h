#pragma once

#include <algorithm>

using namespace std;

namespace math {

inline uint64_t gcd64(uint64_t a, uint64_t b) {
  if (!a || !b) {
    return a | b;
  }
  auto shift = __builtin_ctzll(a | b);
  printf("shift:%d\n", shift);
  a >>= __builtin_ctzll(a);
  printf("\ta:%llu\n", a);
  do {
    printf("\ta:%llu b:%llu\n", a, b);
    b >>= __builtin_ctzll(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
    // printf("\ta:%llu b:%llu\n", a, b);
  } while (b);
  printf("\ta:%llu\n", a);
  return a << shift;
}

} // namespace math
