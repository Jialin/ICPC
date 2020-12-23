#pragma once

#ifndef LOCAL

#define DEBUG_BEGIN
#define DEBUG_END

#define DEBUGF(fmt, ...)

#define DEBUGV(v)
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

#include <complex>

using namespace std;

#define DEBUG_BEGIN fprintf(stderr, "\033[94m")
#ifdef DEBUG_STACKTRACE
#define DEBUG_END                                                              \
  fprintf(                                                                     \
      stderr,                                                                  \
      "\033[0m\n\033[92m^^^^^ %s @ %d ^^^^^\n%s\033[0m\n",                     \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())
#else
#define DEBUG_END                                                              \
  fprintf(                                                                     \
      stderr,                                                                  \
      "\033[0m\n\033[92m^^^^^ %s @ %d ^^^^^\033[0m\n",                         \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__)
#endif

// TODO: Potential simplification:
//   https://www.geeksforgeeks.org/variable-length-arguments-for-macros/
#define DEBUG_STACKTRACE(fmt, args...)                                         \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\n%s\033[0m").c_str(),            \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args,                                                                    \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())

#define DEBUGF(fmt, ...)                                                       \
  DEBUG_BEGIN;                                                                 \
  fprintf(stderr, fmt, ##__VA_ARGS__);                                         \
  DEBUG_END

#define DEBUGF_LT(x, y, fmt, ...)                                              \
  if (x >= y) {                                                                \
    DEBUGF(fmt, ##__VA_ARGS__);                                                \
  }

#define DEBUGF_GE(x, y, fmt, ...)                                              \
  if (x < 0) {                                                                 \
    DEBUGF(fmt, ##__VA_ARGS__);                                                \
  }

#define DEBUGF_NE(x, y, fmt, ...)                                              \
  if (x == y) {                                                                \
    DEBUGF(fmt, ##__VA_ARGS__);                                                \
  }

#define DEBUGF_TRUE(statement, fmt, ...)                                       \
  if (!(statement)) {                                                          \
    DEBUGF(fmt, ##__VA_ARGS__);                                                \
  }

#define DEBUGV(v)                                                              \
  DEBUG_BEGIN;                                                                 \
  debugv(v, #v);                                                               \
  DEBUG_END

#define DEBUGBIT(v)                                                            \
  DEBUG_BEGIN;                                                                 \
  debugBit(v, #v);                                                             \
  DEBUG_END

#define DEBUG_EQ(x, y)                                                         \
  if (x != y) {                                                                \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should be equal to ");                                   \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_FALSE(statement)                                                 \
  if (statement) {                                                             \
    DEBUG_BEGIN;                                                               \
    fprintf(stderr, "%s should be false.", #statement);                        \
    DEBUG_END;                                                                 \
  }

#define DEBUG_LE(x, y)                                                         \
  if (x > y) {                                                                 \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should NOT be greater than ");                           \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_LT(x, y)                                                         \
  if (x >= y) {                                                                \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should be less than ");                                  \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_GE(x, y, ...)                                                    \
  if (x < y) {                                                                 \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should NOT be less than ");                              \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_GT(x, y, ...)                                                    \
  if (x <= y) {                                                                \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should be greater than ");                               \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_NE(x, y, ...)                                                    \
  if (x == y) {                                                                \
    DEBUG_BEGIN;                                                               \
    debugv(x, #x);                                                             \
    fprintf(stderr, " should NOT be equal to ");                               \
    debugv(y, #y);                                                             \
    DEBUG_END;                                                                 \
  }

#define DEBUG_TRUE(statement)                                                  \
  if (!(statement)) {                                                          \
    DEBUG_BEGIN;                                                               \
    fprintf(stderr, "%s should be true.", #statement);                         \
    DEBUG_END;                                                                 \
  }

void debugv(bool v, const string& name) {
  fprintf(stderr, "bool`%s`:(%s)", name.c_str(), v ? "true" : "false");
}

void debugv(char v, const string& name) {
  fprintf(stderr, "char`%s`:(%c)", name.c_str(), v);
}

void debugv(int v, const string& name) {
  fprintf(stderr, "int`%s`:(%d)", name.c_str(), v);
}

void debugv(int64_t v, const string& name) {
  fprintf(stderr, "int`%s`:(%lld)", name.c_str(), v);
}

void debugv(double v, const string& name) {
  fprintf(stderr, "double`%s`:(%lf)", name.c_str(), v);
}

void debugv(const char* v, const string& name) {
  fprintf(stderr, "char*`%s`:(%s)", name.c_str(), v);
}

template<typename T>
void debugv(const T* v, const string& name) {
  fprintf(
      stderr,
      "%s*`%s`:(%ld)",
      typeid(T).name(),
      name.c_str(),
      reinterpret_cast<intptr_t>(v));
}

void debugv(const string& v, const string& name) {
  fprintf(stderr, "string`%s`:(%s)", name.c_str(), v.c_str());
}

void debugv(const vector<int>& vs, const string& name) {
  fprintf(stderr, "vector<int>`%s`(size:%lu):[", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]);
    }
  }
  fprintf(stderr, "]");
}

void debugv(const vector<complex<double>>& vs, const string& name) {
  fprintf(
      stderr,
      "vector<complex<double>>`%s`(size:%lu):[",
      name.c_str(),
      vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "(%lf)+(%lf)i", vs.front().real(), vs.front().imag());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",(%lf)+(%lf)i", vs[i].real(), vs[i].imag());
    }
  }
  fprintf(stderr, "]");
}

template<typename V>
void debugBit(V v, const string& name) {
  fprintf(stderr, "bit`%s`[", name.c_str());
  if (v == 0) {
    fprintf(stderr, "0");
    return;
  }
  if (v < 0) {
    fprintf(stderr, "-");
    v = -v;
  }
  vector<int> bits;
  for (int cnt = 0; v > 0 && cnt < 256; ++cnt, v >>= 1) {
    bits.emplace_back(v & 1);
  }
  reverse(bits.begin(), bits.end());
  for (int bit : bits) {
    fprintf(stderr, "%d", bit);
  }
  fprintf(stderr, "]");
}
#endif
