#pragma once

#include "debug/debug_basic.h"

using namespace std;

template<typename MATRIX>
void debugv(
    const MATRIX& mat,
    const string& name,
    const string& prettyFunction,
    int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "matrix`%s` n:%d m:%d\n", name.c_str(), mat._n, mat._m);
  for (int i = 0; i < mat._n; ++i) {
    for (int j = 0; j < mat._m; ++j) {
      fprintf(stderr, "\t%d", mat._vs[i][j]);
    }
    fprintf(stderr, "\n");
  }
  DEBUG_END;
}
