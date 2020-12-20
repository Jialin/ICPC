#pragma once

#include "debug/debug_basic.h"
#include "math/bigint.h"

using namespace std;

namespace math {

template<int GROUP, typename BASE_SQR>
struct BigInt;

} // namespace math

template<int GROUP, typename BASE_SQR>
void debugv(const math::BigInt<GROUP, BASE_SQR>& v, const string& name) {
  fprintf(stderr, "Bigint<%d>`%s`: \n", GROUP, name.c_str());
  int idx = static_cast<int>(v._vs.size()) - 1;
  fprintf(stderr, "%d", v._vs[idx]);
  for (int i = idx - 1; i >= 0; --i) {
    fprintf(stderr, "|%0*d", GROUP, v._vs[i]);
  }
}
