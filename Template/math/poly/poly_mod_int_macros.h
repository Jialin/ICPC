#ifdef POLY_MOD_INT_ALL
#define POLY_MOD_INT_ASSIGN_INT_VECTOR
#define POLY_MOD_INT_ADD_INLINE
#define POLY_MOD_INT_CONSTRUCT
#define POLY_MOD_INT_FFT_INV
#define POLY_MOD_INT_FFT_INV_INLINE
#define POLY_MOD_INT_FFT_RECURRENCE_INLINE
#define POLY_MOD_INT_MUL_INLINE_INT
#define POLY_MOD_INT_MUL_INT
#define POLY_MOD_INT_NEGATE_INLINE
#define POLY_MOD_INT_NTT_MUL_INLINE_MODIFY
#define POLY_MOD_INT_NTT_NTT_INLINE
#define POLY_MOD_INT_NTT_RECURRENCE_INLINE
#define POLY_MOD_INT_SHRINK
#define POLY_MOD_INT_SUB
#endif

#ifdef POLY_MOD_INT_FFT_RECURRENCE_INLINE
#define FFT_UTILS_RECURRENCE_INLINE_MOD
#endif

#ifdef POLY_MOD_INT_NTT_MUL_INLINE_MODIFY
#define NTT_UTILS_FIX_MUL_INLINE_MODIFY
#endif

#ifdef POLY_MOD_INT_NEGATE_INLINE
#define MOD_INT_NEGATE_INLINE
#endif

#ifdef POLY_MOD_INT_FFT_INV
#define POLY_MOD_INT_FFT_INV_INLINE
#endif

#ifdef POLY_MOD_INT_FFT_INV_INLINE
#define MOD_INT_INV_INLINE
#define POLY_MOD_INT_ADD_INLINE
#define POLY_MOD_INT_FFT_MUL_INLINE
#define POLY_MOD_INT_MUL_INLINE_INT
#define POLY_MOD_INT_NEGATE_INLINE
#endif

#ifdef POLY_MOD_INT_ADD_INLINE
#define MOD_INT_ADD_INLINE
#endif

#ifdef POLY_MOD_INT_MUL_INT
#define POLY_MOD_INT_MUL_INLINE_INT
#endif

#ifdef POLY_MOD_INT_FFT_MUL_INLINE
#define FFT_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef POLY_MOD_INT_SUB
#define MOD_INT_ADD_INLINE
#define MOD_INT_SUB_INLINE
#endif

#if defined(POLY_MOD_INT_FFT_INV) || defined(POLY_MOD_INT_FFT_INV_INLINE) ||   \
    defined(POLY_MOD_INT_FFT_RECURRENCE_INLINE)
#define _POLY_MOD_INT_FFT_UTILS
#endif

#if defined(POLY_MOD_INT_NTT_MUL_INLINE_MODIFY) ||                             \
    defined(POLY_MOD_INT_NTT_NTT_INLINE) ||                                    \
    defined(POLY_MOD_INT_NTT_RECURRENCE_INLINE)
#define _POLY_MOD_INT_NTT_UTILS_FIX
#endif

#include "math/fft/ntt_utils_fix_macros.h"
#include "math/mod/mod_int_macros.h"
