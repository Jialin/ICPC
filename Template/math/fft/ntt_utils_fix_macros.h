#ifdef NTT_UTILS_FIX_ALL
#define NTT_UTILS_FIX_MUL_INLINE_MODIFY
#define NTT_UTILS_FIX_ONLINE
#endif

#ifdef NTT_UTILS_FIX_ONLINE
#define NTT_UTILS_FIX_MUL_INLINE_MODIFY
#endif

#define MOD_INT_EXP
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE

#include "math/mod/mod_int_macros.h"
