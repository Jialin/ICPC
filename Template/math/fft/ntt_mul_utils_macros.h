#ifdef NTT_MUL_UTILS_ALL
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define MOD_INT_MUL_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_MUL_UTILS_MOD_INT
#endif

#ifdef _NTT_MUL_UTILS_MOD_INT
#include "math/mod/mod_int_macros.h"
#endif

#include "math/fft/ntt_utils_macros.h"
