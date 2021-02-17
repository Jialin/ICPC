#ifdef NTT_MUL_UTILS_ALL
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#define MOD_INT_TYPEDEF_V

#ifdef NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define MOD_INT_CONST_MOD
#define MOD_INT_MUL_INLINE
#define MOD_INT_TYPEDEF_V_SQR
#define NTT_UTILS_NTT_MOD_INT
#endif

#include "math/fft/ntt_utils_macros.h"
