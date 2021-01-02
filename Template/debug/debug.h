#pragma once

#include "debug/debug_basic.h"

#ifdef LOCAL
#include "debug/debug_bigint.h"
#include "debug/debug_matrix.h"

using namespace std;

template<typename T>
inline string totype(const vector<T>& vs) {
  return "vector<" + (!vs.empty() ? totype(*vs.data()) : "") + ">";
}

template<typename T>
inline string tostring(const vector<T>& vs) {
  stringstream ss;
  ss << "[";
  if (!vs.empty()) {
    ss << tostring(vs.front());
    for (size_t i = 1; i < vs.size(); ++i) {
      if (i < 100) {
        ss << "," << tostring(vs[i]);
      } else {
        ss << ",..." << vs.size() - i << " more";
        break;
      }
    }
  }
  ss << "]";
  return ss.str();
}
#endif
