#ifdef NTT_ONLINE_UTILS_ALL
#define NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
#endif

#define MOD_INT_TYPEDEF_V

#ifdef NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
#define MOD_INT_ADD_INLINE
#define MOD_INT_CONST_MOD
#define MOD_INT_TYPEDEF_V_SQR
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#include "math/fft/ntt_mul_utils_macros.h"
#include "math/mod/mod_int_macros.h"
