#pragma once

#ifndef LOCAL

#define DEBUG(args...)
#define DEBUG_EQ(x, y)

#else

#define DEBUG_BEGIN fprintf(stderr, "\033[94m[%d] ", __LINE__);
#define DEBUG_END fprintf(stderr, "\033[0m");
#define DEBUG(args...)                                                         \
  DEBUG_BEGIN;                                                                 \
  fprintf(stderr, args);                                                       \
  DEBUG_END
#define DEBUG_EQ(x, y)                                                         \
  if (x != y) {                                                                \
    DEBUG("%d != %d\n", x, y);                                                 \
  }
#endif
