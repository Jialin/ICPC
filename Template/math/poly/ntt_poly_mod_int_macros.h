#ifdef NTT_POLY_MOD_INT_ALL
#define NTT_POLY_MOD_INT_ASSIGN_VECTOR
#define NTT_POLY_MOD_INT_CONSTRUCT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_EXP_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_LN_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#define NTT_POLY_MOD_INT_ONLINE_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#endif

#ifdef NTT_POLY_MOD_INT_EXP_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_DIV_INLINE
#define MOD_INT_INIT_SUB
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV
#define NTT_POLY_MOD_INT_LN_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#define _NTT_POLY_MOD_INT_EXP
#define _NTT_POLY_MOD_INT_INV
#endif

#ifdef NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define MOD_INT_DIV_INLINE
#define MOD_INT_MUL_INLINE
#endif

#ifdef NTT_POLY_MOD_INT_INV
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#endif

#ifdef NTT_POLY_MOD_INT_INV_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#endif

#ifdef NTT_POLY_MOD_INT_LN_INLINE
#define MOD_INT_DIV_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_INV
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef NTT_POLY_MOD_INT_ONLINE_INLINE
#define NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
#define _NTT_POLY_MOD_INT_ONLINE_UTILS
#endif

#ifdef _NTT_POLY_MOD_INT_EXP
#define MOD_INT_ADD_INLINE
#define MOD_INT_DIV_INLINE
#define MOD_INT_INIT_SUB
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV
#define NTT_POLY_MOD_INT_LN_INLINE
#define _NTT_POLY_MOD_INT_INV
#endif

#ifdef _NTT_POLY_MOD_INT_INV
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef _NTT_POLY_MOD_INT_ONLINE_UTILS
#include "math/fft/ntt_online_utils_macros.h"
#endif

#include "math/fft/ntt_mul_utils_macros.h"