#ifdef NTT_POLY_MOD_INT_ALL
#define NTT_POLY_MOD_INT_ASSIGN
#define NTT_POLY_MOD_INT_ASSIGN_VECTOR
#define NTT_POLY_MOD_INT_CONSTRUCT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_DIV_INLINE
#define NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED
#define NTT_POLY_MOD_INT_DOT
#define NTT_POLY_MOD_INT_EXP_INLINE
#define NTT_POLY_MOD_INT_EXTEND
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_LN_INLINE
#define NTT_POLY_MOD_INT_MOD_INLINE
#define NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#define NTT_POLY_MOD_INT_ONLINE_INLINE
#define NTT_POLY_MOD_INT_RECURRENCE
#define NTT_POLY_MOD_INT_SHRINK
#define NTT_POLY_MOD_INT_SUB_INLINE
#endif

#ifdef NTT_POLY_MOD_INT_DIV_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_ASSIGN
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_DOT
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_MUL
#endif

#ifdef NTT_POLY_MOD_INT_EXP_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_SUB
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_LN_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_EXP
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#endif

#ifdef NTT_POLY_MOD_INT_INV
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_INV_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_LN_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_MOD_INLINE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_ASSIGN
#define NTT_POLY_MOD_INT_DIV_INLINE
#define NTT_POLY_MOD_INT_EXTEND
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_SHRINK
#define NTT_POLY_MOD_INT_SUB_INLINE
#define NTT_POLY_MOD_SHRINK
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED
#define MOD_INT_SUB_INLINE
#define NTT_POLY_MOD_INT_ASSIGN
#define NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED
#define NTT_POLY_MOD_INT_EXTEND
#define NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#endif

#ifdef NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_ONLINE_INLINE
#define NTT_ONLINE_UTILS_ONLINE_INLINE_MOD_INT
#define _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_RECURRENCE
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_MUL
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_ASSIGN
#define NTT_POLY_MOD_INT_DIV_INLINE_PRECOMPUTED
#define NTT_POLY_MOD_INT_DOT
#define NTT_POLY_MOD_INT_EXTEND
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_MOD_INLINE_PRECOMPUTED
#define NTT_POLY_MOD_INT_MUL_INLINE
#define NTT_POLY_MOD_INT_MUL_INLINE_CYCLIC
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef NTT_POLY_MOD_INT_SUB_INLINE
#define MOD_INT_SUB_INLINE
#define NTT_POLY_MOD_INT_EXTEND
#define NTT_POLY_MOD_SHRINK
#endif

#ifdef _NTT_POLY_MOD_INT_EXP
#define MOD_INT_ADD_INLINE
#define MOD_INT_INIT_SUB
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_MUL_UTILS_MUL_INLINE_MOD_INT
#define NTT_POLY_MOD_INT_DERIVE_INLINE
#define NTT_POLY_MOD_INT_INTEGRAL_INLINE
#define NTT_POLY_MOD_INT_INV_INLINE
#define NTT_POLY_MOD_INT_LN_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_INV
#define _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef _NTT_POLY_MOD_INT_INV
#define MOD_INT_ADD_INLINE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define NTT_UTILS_NTT_MOD_INT
#define _NTT_POLY_MOD_INT_NTT_UTILS
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_MUL_UTILS
#include "math/fft/ntt_mul_utils_macros.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_ONLINE_UTILS
#include "math/fft/ntt_online_utils_macros.h"
#endif

#ifdef _NTT_POLY_MOD_INT_NTT_UTILS
#include "math/fft/ntt_utils_macros.h"
#endif

#include "math/mod/mod_int_macros.h"
