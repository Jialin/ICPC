#pragma once

#include "debug/debug_basic.h"

#ifdef LOCAL
#include "debug/debug_matrix.h"

using namespace std;

template<typename X, typename Y>
inline string totype(const pair<X, Y>& vs) {
  return "pair<" + totype(vs.first) + "," + totype(vs.second) + ">";
}

template<typename T>
inline string totype(const vector<T>& vs) {
  return "vector<" + (!vs.empty() ? totype(*vs.data()) : "") + ">";
}

template<typename K, typename V>
inline string totype(const unordered_map<K, V>& vs) {
  return "unordered_map<" +
         (vs.empty() ? "" : totype(vs.begin()->first) + "," + totype(vs.begin()->second)) + ">";
}

template<typename X, typename Y>
inline string tostring(const pair<X, Y>& vs) {
  return "<" + tostring(vs.first) + "," + tostring(vs.second) + ">";
}

template<typename T>
inline string tostring(const vector<T>& vs) {
  stringstream ss;
  ss << "[";
  if (!vs.empty()) {
    ss << tostring(vs.front());
    for (size_t i = 1; i < vs.size(); ++i) {
      if (i < 16) {
        ss << "," << tostring(vs[i]);
      } else {
        ss << ",...";
        break;
      }
    }
  }
  ss << "](" << vs.size() << " elements)";
  return ss.str();
}

template<typename K, typename V>
inline string tostring(const unordered_map<K, V>& vs) {
  stringstream ss;
  ss << "{";
  int i = 0;
  for (const auto& [k, v] : vs) {
    if (i >= 16) {
      ss << ",...";
      break;
    }
    if (i) {
      ss << ",";
    }
    ss << tostring(k) << ":" << tostring(v);
    ++i;
  }
  ss << "}(" << vs.size() << " tuples)";
  return ss.str();
}

template<typename... VS>
inline string tostring2(VS const&... vs) {
  stringstream ss;
  int i = 0;
  (
      [&](const auto& v) {
        if (i) {
          ss << ((i & 1) ? ':' : ',');
        }
        ++i;
        ss << tostring(v);
      }(vs),
      ...);
  return ss.str();
}
#endif
