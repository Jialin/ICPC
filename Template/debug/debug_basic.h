#pragma once

#ifndef LOCAL

#define DEBUG_BEGIN
#define DEBUG_END

#define DEBUGF(fmt, args...)
#define DEBUGV(v)
#define DEBUGBIT(v)
#define DEBUG_EQ(x, y)
#define DEBUG_FALSE(statement, fmt, args...)
#define DEBUG_TRUE(statement, fmt, args...)

#else

#include <boost/stacktrace.hpp>

using namespace std;

#define DEBUG_BEGIN                                                            \
  fprintf(stderr, "\033[94m==[%s][L%d]==\n", __PRETTY_FUNCTION__, __LINE__)
#define DEBUG_END fprintf(stderr, "\n\033[0m")

#define DEBUG_STACKTRACE(fmt, args...)                                         \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\n%s\033[0m").c_str(),            \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args,                                                                    \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())

#define DEBUGV(v)                                                              \
  DEBUG_BEGIN;                                                                 \
  debugv(v, #v);                                                               \
  DEBUG_END

#define DEBUGBIT(v)                                                            \
  DEBUG_BEGIN;                                                                 \
  debugBit(v, #v);                                                             \
  DEBUG_END

#define DEBUGF(fmt, args...)                                                   \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\033[0m").c_str(),                \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args)

#define DEBUG_EQ(x, y)                                                         \
  if (x != y) {                                                                \
    DEBUG_STACKTRACE("%d != %d\n", x, y);                                      \
  }

#define DEBUG_FALSE(statement, fmt, args...)                                   \
  if (statement) {                                                             \
    DEBUG_STACKTRACE(fmt, args);                                               \
  }

#define DEBUG_TRUE(statement, fmt, args...)                                    \
  if (!(statement)) {                                                          \
    DEBUG_STACKTRACE(fmt, args);                                               \
  }

void debugv(int64_t v, const string& name) {
  fprintf(stderr, "int64_t`%s`= %lld", name.c_str(), v);
}

void debugv(int v, const string& name) {
  fprintf(stderr, "int`%s`= %d", name.c_str(), v);
}

void debugv(const char* v, const string& name) {
  fprintf(stderr, "char*`%s`= %s", name.c_str(), v);
}

void debugv(const string& v, const string& name) {
  fprintf(stderr, "string`%s`= %s", name.c_str(), v.c_str());
}

void debugv(const vector<int>& vs, const string& name) {
  fprintf(stderr, "vector<int>`%s`(size:%lu)= [", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]);
    }
  }
  fprintf(stderr, "]");
}

template<typename V>
void debugBit(V v, const string& name) {
  fprintf(stderr, "bit`%s`= ", name.c_str());
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
}

#endif
