#pragma once

#ifndef LOCAL

#define DEBUG(fmt, args...)

#define DEBUG_EQ(x, y)

#define DEBUG_TRUE(statement, fmt, args...)

#else

#define DEBUG(fmt, args...)                                                    \
  fprintf(                                                                     \
      stderr,                                                                  \
      ("\033[94m[%s][L%d] " + string(fmt) + "\033[0m").c_str(),                \
      __PRETTY_FUNCTION__,                                                     \
      __LINE__,                                                                \
      args)

#define DEBUG_EQ(x, y)                                                         \
  if (x != y) {                                                                \
    DEBUG("%d != %d\n", x, y);                                                 \
  }

#define DEBUG_TRUE(statement, fmt, args...)                                    \
  if (statement) {                                                             \
    DEBUG(fmt, args);                                                          \
  }
#endif
