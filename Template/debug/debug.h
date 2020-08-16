#pragma once

#ifndef LOCAL

#define DEBUG(args...)

#else

#define DEBUG_BEGIN fprintf(stderr, "\033[94m");
#define DEBUG_END fprintf(stderr, "\033[0m");
#define DEBUG(args...)                                                         \
  DEBUG_BEGIN;                                                                 \
  fprintf(stderr, args);                                                       \
  DEBUG_END

#endif
