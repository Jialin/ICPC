#pragma once

#include "debug/debug_basic.h"

#ifdef LOCAL
#include "debug/debug_matrix.h"

using namespace std;

template<typename X, typename Y>
inline string totype(const pair<X, Y>& vs) {
  return "pair<" + totype(vs.first) + "," + totype(vs.second) + ">";
}

template<typename A, typename B, typename C>
inline string totype(const tuple<A, B, C>& v) {
  return "tuple<" + totype(get<0>(v)) + "," + totype(get<1>(v)) + "," + totype(get<2>(v)) + ">";
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

template<typename K, typename V>
inline string totype(const map<K, V>& vs) {
  return "map<" + (vs.empty() ? "" : totype(vs.begin()->first) + "," + totype(vs.begin()->second)) +
         ">";
}

template<typename K>
inline string totype(const unordered_set<K>& vs) {
  return "unordered_set<" + (vs.empty() ? "" : totype(*vs.begin())) + ">";
}

template<typename K>
inline string totype(const set<K>& vs) {
  return "set<" + (vs.empty() ? "" : totype(*vs.begin())) + ">";
}

template<typename X, typename Y>
inline string tostring(const pair<X, Y>& vs) {
  return "<" + tostring(vs.first) + "," + tostring(vs.second) + ">";
}

template<typename A, typename B, typename C>
ostream& operator<<(ostream& o, const tuple<A, B, C>& v) {
  return o << '(' << tostring(get<0>(v)) << ',' << tostring(get<1>(v)) << ',' << tostring(get<2>(v))
           << ')';
}

template<typename T>
inline string tostring(const vector<vector<T>>& vs) {
  stringstream ss;
  ss << "[";
  if (!vs.empty()) {
    for (size_t i = 0; i < vs.size(); ++i) {
      if (!i) {
        ss << endl;
      }
      ss << "  ";
      if (i < 16) {
        ss << tostring(vs[i]) << ',' << endl;
      } else {
        ss << "...," << endl;
        break;
      }
    }
  }
  ss << "](" << vs.size() << " elements)";
  return ss.str();
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

template<typename K>
inline string tostring(const unordered_set<K>& vs) {
  stringstream ss;
  ss << "{";
  int i = 0;
  for (const auto& v : vs) {
    if (i >= 16) {
      ss << ",...";
      break;
    }
    if (i) {
      ss << ",";
    }
    ss << tostring(v);
    ++i;
  }
  ss << "}(" << vs.size() << " elements)";
  return ss.str();
}

template<typename K>
inline string tostring(const set<K>& vs) {
  stringstream ss;
  ss << "{";
  int i = 0;
  for (const auto& v : vs) {
    if (i >= 16) {
      ss << ",...";
      break;
    }
    if (i) {
      ss << ",";
    }
    ss << tostring(v);
    ++i;
  }
  ss << "}(" << vs.size() << " elements)";
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

template<typename K, typename V>
inline string tostring(const map<K, V>& vs) {
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

template<typename V>
inline string tostring(V v, int base) {
  stringstream ss;
  bool negative = false;
  if (v < 0) {
    negative = true;
    v = -v;
  }
  if (!v) {
    ss << '0';
  } else {
    for (; v; v /= base) {
      int digit = v % base;
      ss << CAST<char>(digit < 10 ? '0' + digit : 'A' + digit - 10);
    }
  }
  string res = ss.str();
  reverse(res.begin(), res.end());
  return (negative ? "-" : "") + res;
}

template<typename... VS>
inline string tostring1(VS const&... vs) {
  stringstream ss;
  int i = 0;
  (
      [&](const auto& v) {
        if (i) {
          ss << ',';
        }
        ++i;
        ss << tostring(v);
      }(vs),
      ...);
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
