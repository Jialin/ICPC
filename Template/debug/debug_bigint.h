#pragma once

#include "debug/debug_basic.h"
#include "math/bigint.h"

using namespace std;

template<int GROUP>
void debugv(const math::BigInt<GROUP>& v, const string& name) {
  fprintf(stderr, "Bigint<%d>`%s`: \n", GROUP, name.c_str());
  int idx = static_cast<int>(v._vs.size()) - 1;
  fprintf(stderr, "%d", v._vs[idx]);
  for (int i = idx - 1; i >= 0; --i) {
    fprintf(stderr, "|%0*d", GROUP, v._vs[i]);
  }
}
