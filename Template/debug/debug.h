#pragma once

#include <iostream>

#include <boost/stacktrace.hpp>

using namespace std;

#ifndef LOCAL

#define DEBUG(fmt, args...)
#define DEBUG_EQ(x, y)
#define DEBUG_FALSE(statement, fmt, args...)
#define DEBUG_TRUE(statement, fmt, args...)

#else

#define DEBUG_STACKTRACE(fmt, args...)                                         \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\n%s\033[0m").c_str(),            \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args,                                                                    \
      boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str());

#define DEBUG(fmt, args...)                                                    \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\033[0m").c_str(),                \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args);

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
