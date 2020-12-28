#pragma once

#include "debug/debug_basic.h"
#include "math/mod/mod_int.h"

using namespace std;

template<typename V_SQR, int MOD>
void debugv(const math::ModInt<int, V_SQR, MOD>& v, const string& name) {
  fprintf(stderr, "ModInt`%s`:%d", name.c_str(), v._v);
}

template<typename V_SQR, int MOD>
void debugv(
    const vector<math::ModInt<int, V_SQR, MOD>>& vs, const string& name) {
  fprintf(stderr, "vector<ModInt>`%s`(size:%lu):[", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front()._v);
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]._v);
    }
  }
  fprintf(stderr, "]");
}
