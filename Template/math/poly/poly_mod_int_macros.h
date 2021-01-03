#ifdef POLY_MOD_INT_ALL
#define POLY_MOD_INT_ACCESS
#define POLY_MOD_INT_CONSTRUCT
#define POLY_MOD_INT_MUL_INLINE_MODIFY
#define POLY_MOD_INT_RESERVE
#define POLY_MOD_INT_RESIZE
#define POLY_MOD_INT_SIZE
#endif

#ifdef POLY_MOD_INT_MUL_INLINE_MODIFY
#define NTT_UTILS_FIX_MUL_INLINE_MODIFY
#define _POLY_MOD_INT_NTT_UTILS_FIX
#endif

#include "math/fft/ntt_utils_fix_macros.h"
#include "math/mod/mod_int_macros.h"
