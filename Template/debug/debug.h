#pragma once

#ifndef LOCAL

#define DEBUGF(fmt, args...)
#define DEBUGV(v)
#define DEBUG_EQ(x, y)
#define DEBUG_FALSE(statement, fmt, args...)
#define DEBUG_TRUE(statement, fmt, args...)

#else

#include <boost/stacktrace.hpp>

#define DEBUG_BEGIN(function, line)                                            \
  fprintf(stderr, "\033[94m[%s][L%d]\n\t", prettyFunction.c_str(), line)
#define DEBUG_END fprintf(stderr, "\n\033[0m")

void debugv(int v, const string& name, const string& prettyFunction, int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "int`%s`= %d", name.c_str(), v);
  DEBUG_END;
}

void debugv(
    const string& v,
    const string& name,
    const string& prettyFunction,
    int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "string`%s`= %s", name.c_str(), v.c_str());
  DEBUG_END;
}

void debugv(
    const vector<int>& vs,
    const string& name,
    const string& prettyFunction,
    int line) {
  DEBUG_BEGIN(prettyFunction, line);
  fprintf(stderr, "vector<int>`%s`(size:%lu)= [", name.c_str(), vs.size());
  if (!vs.empty()) {
    fprintf(stderr, "%d", vs.front());
    for (int i = 1; i < (int)vs.size(); ++i) {
      fprintf(stderr, ",%d", vs[i]);
    }
  }
  fprintf(stderr, "]");
  DEBUG_END;
}

#define DEBUG_STACKTRACE(fmt, args...)                                         \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\n%s\033[0m").c_str(),            \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args,                                                                    \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str())

#define DEBUGV(v) debugv(v, #v, __PRETTY_FUNCTION__, __LINE__)

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

#endif
