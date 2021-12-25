#pragma once

#ifndef LOCAL

#define DEBUG_BEGIN
#define DEBUG_END

#define DEBUGF(fmt, ...)

#define DEBUGV(v)
#define DEBUGV1(v)
#define DEBUGV2(v1, v2)
#define DEBUGV3(v1, v2, v3)
#define DEBUGV4(v1, v2, v3, v4)
#define DEBUGV5(v1, v2, v3, v4, v5)
#define DEBUGV6(v1, v2, v3, v4, v5, v6)
#define DEBUGVS(v, ...)
#define DEBUGBIT(v)

#define DEBUG_EQ(x, y)
#define DEBUG_FALSE(statement)
#define DEBUG_GE(x, y)
#define DEBUG_GT(x, y)
#define DEBUG_LE(x, y)
#define DEBUG_LT(x, y)
#define DEBUG_NE(x, y)
#define DEBUG_TRUE(statement)

#define DEBUGF_TRUE(statement, fmt, ...)
#define DEBUGF_NE(x, y, fmt, ...)
#define DEBUGF_GE(x, y, fmt, ...)

#else

#ifdef DEBUG_STACKTRACE
#include <boost/stacktrace.hpp>
#endif

using namespace std;

#define DEBUG_BEGIN fprintf(stderr, "\033[94m")
#ifdef DEBUG_STACKTRACE
#define DEBUG_END                                                                                  \
  fprintf(                                                                                         \
      stderr,                                                                                      \
      "\033[0m\n\033[92m^^^^^ %s @ %d ^^^^^\n%s\033[0m\n",                                         \
      __PRETTY_FUNCTION__,                                                                         \
      __LINE__,                                                                                    \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())
#else
#define DEBUG_END                                                                                  \
  fprintf(stderr, "\033[0m\033[92m^^^^^ %s @ %d ^^^^^\033[0m\n", __PRETTY_FUNCTION__, __LINE__)
#endif

// TODO: Potential simplification:
//   https://www.geeksforgeeks.org/variable-length-arguments-for-macros/
#define DEBUG_STACKTRACE(fmt, args...)                                                             \
  fprintf(                                                                                         \
      stderr,                                                                                      \
      ("\033[94m[%s][L%d] " + string(fmt) + "\n%s\033[0m").c_str(),                                \
      __PRETTY_FUNCTION__,                                                                         \
      __LINE__,                                                                                    \
      args,                                                                                        \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())

#define DEBUGF(fmt, ...)                                                                           \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, fmt, ##__VA_ARGS__);                                                             \
  DEBUG_END

#define DEBUGF_LT(x, y, fmt, ...)                                                                  \
  if (x >= y) {                                                                                    \
    DEBUGF(fmt, ##__VA_ARGS__);                                                                    \
  }

#define DEBUGF_GE(x, y, fmt, ...)                                                                  \
  if (x < 0) {                                                                                     \
    DEBUGF(fmt, ##__VA_ARGS__);                                                                    \
  }

#define DEBUGF_NE(x, y, fmt, ...)                                                                  \
  if (x == y) {                                                                                    \
    DEBUGF(fmt, ##__VA_ARGS__);                                                                    \
  }

#define DEBUGF_TRUE(statement, fmt, ...)                                                           \
  if (!(statement)) {                                                                              \
    DEBUGF(fmt, ##__VA_ARGS__);                                                                    \
  }

#define _DEBUGV(v) fprintf(stderr, "%s`%s`:%s\n", totype(v).c_str(), #v, tostring(v).c_str());

#define DEBUGV(v)                                                                                  \
  DEBUG_BEGIN;                                                                                     \
  _DEBUGV(v);                                                                                      \
  DEBUG_END

#define DEBUGV2(v1, v2)                                                                            \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, "%s\n", tostring2(#v1, v1, #v2, v2).c_str());                                    \
  DEBUG_END

#define DEBUGV3(v1, v2, v3)                                                                        \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, "%s\n", tostring2(#v1, v1, #v2, v2, #v3, v3).c_str());                           \
  DEBUG_END

#define DEBUGV4(v1, v2, v3, v4)                                                                    \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, "%s\n", tostring2(#v1, v1, #v2, v2, #v3, v3, #v4, v4).c_str());                  \
  DEBUG_END

#define DEBUGV5(v1, v2, v3, v4, v5)                                                                \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, "%s\n", tostring2(#v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5).c_str());         \
  DEBUG_END

#define DEBUGV6(v1, v2, v3, v4, v5, v6)                                                            \
  DEBUG_BEGIN;                                                                                     \
  fprintf(                                                                                         \
      stderr, "%s\n", tostring2(#v1, v1, #v2, v2, #v3, v3, #v4, v4, #v5, v5, #v6, v6).c_str());    \
  DEBUG_END

#define DEBUGVS(v, ...)                                                                            \
  DEBUG_BEGIN;                                                                                     \
  fprintf(stderr, "%s\n", tostring1(v, ##__VA_ARGS__).c_str());                                    \
  DEBUG_END

#define DEBUGBIT(v)                                                                                \
  DEBUG_BEGIN;                                                                                     \
  debugBit(v, #v);                                                                                 \
  DEBUG_END

#define DEBUG_EQ(x, y)                                                                             \
  if ((x) != (y)) {                                                                                \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should be equal to ");                                                       \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_FALSE(statement)                                                                     \
  if (statement) {                                                                                 \
    DEBUG_BEGIN;                                                                                   \
    fprintf(stderr, "%s should be false.", #statement);                                            \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_LE(x, y)                                                                             \
  if ((x) > (y)) {                                                                                 \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should NOT be greater than ");                                               \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_LT(x, y)                                                                             \
  if ((x) >= (y)) {                                                                                \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should be less than ");                                                      \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_GE(x, y, ...)                                                                        \
  if ((x) < (y)) {                                                                                 \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should NOT be less than ");                                                  \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_GT(x, y, ...)                                                                        \
  if ((x) <= (y)) {                                                                                \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should be greater than ");                                                   \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_NE(x, y, ...)                                                                        \
  if ((x) == (y)) {                                                                                \
    DEBUG_BEGIN;                                                                                   \
    _DEBUGV(x);                                                                                    \
    fprintf(stderr, " should NOT be equal to ");                                                   \
    _DEBUGV(y);                                                                                    \
    DEBUG_END;                                                                                     \
  }

#define DEBUG_TRUE(statement)                                                                      \
  if (!(statement)) {                                                                              \
    DEBUG_BEGIN;                                                                                   \
    fprintf(stderr, "%s should be true.", #statement);                                             \
    DEBUG_END;                                                                                     \
  }

inline string totype(bool v) {
  return "bool";
}

inline string totype(const vector<bool>& vs) {
  return "vector<bool>";
}

inline string totype(char v) {
  return "char";
}

inline string totype(int v) {
  return "int";
}

inline string tostring(int v) {
  stringstream ss;
  ss << v;
  return ss.str();
}

inline string tostring(int64_t v) {
  stringstream ss;
  ss << v;
  return ss.str();
}

inline string totype(int64_t v) {
  return "int64";
}

inline string totype(uint64_t v) {
  return "uint64";
}

inline string totype(__int128_t v) {
  return "int128";
}

inline string totype(__uint128_t v) {
  return "uint128";
}

inline string totype(double v) {
  return "double";
}

inline string totype(long double v) {
  return "long double";
}

inline string totype(const char* v) {
  return "const char*";
}

inline string totype(char* v) {
  return "char*";
}

inline string totype(const string& v) {
  return "string";
}

inline string totype(const nullptr_t& v) {
  return "null_t";
}

inline string tostring(const nullptr_t& v) {
  return "null";
}

template<typename T>
inline string totype(const T& v) {
  return typeid(decltype(v)).name();
}

ostream& operator<<(ostream& o, __int128_t x) {
  if (x == std::numeric_limits<__int128_t>::min()) {
    return o << "-170141183460469231731687303715884105728";
  }
  if (x < 0) {
    return o << "-" << -x;
  }
  if (x < 10) {
    return o << (char)(x + '0');
  }
  return o << x / 10 << (char)(x % 10 + '0');
}

template<typename T>
inline string tostring(const T& v) {
  stringstream ss;
  ss << boolalpha << v;
  return ss.str();
}

#endif
