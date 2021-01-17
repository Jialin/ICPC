#ifdef NTT_POLY_MOD_INT_ALL
#define NTT_POLY_MOD_INT_ASSIGN_VECTOR
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#include "math/fft/ntt_mul_utils_macros.h"
