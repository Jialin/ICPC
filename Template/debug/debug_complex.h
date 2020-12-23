#pragma once

#include "debug/debug_basic.h"
#include "math/complex/complex.h"

using namespace std;

void debugv(const math::Complex<double>& v, const string& name) {
  fprintf(
      stderr, "Complex<double>`%s`:(%lf)+(%lf)i", name.c_str(), v.real, v.imag);
}

void debugv(const math::Complex<long double>& v, const string& name) {
  fprintf(
      stderr,
      "Complex<long double>`%s`:(%Lf)+(%Lf)i",
      name.c_str(),
      v.real,
      v.imag);
}

void debugv(const vector<math::Complex<double>>& vs, const string& name) {
  fprintf(
      stderr,
      "vector<Complex<double>>`%s`(size:%lu):[",
      name.c_str(),
      vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "(%lf)+(%lf)i", vs.front().real, vs.front().imag);
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",(%lf)+(%lf)i", vs[i].real, vs[i].imag);
    }
  }
  fprintf(stderr, "]");
}

void debugv(const vector<math::Complex<long double>>& vs, const string& name) {
  fprintf(
      stderr,
      "vector<Complex<long double>>`%s`(size:%lu):[",
      name.c_str(),
      vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "(%Lf)+(%Lf)i", vs.front().real, vs.front().imag);
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",(%Lf)+(%Lf)i", vs[i].real, vs[i].imag);
    }
  }
  fprintf(stderr, "]");
}
