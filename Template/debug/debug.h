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

#include "debug/debug_basic.h"
#include "debug/debug_bigint.h"
#include "debug/debug_matrix.h"

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

#endif
