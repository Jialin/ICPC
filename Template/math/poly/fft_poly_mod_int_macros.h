#ifdef FFT_POLY_MOD_INT_ALL
#define FFT_POLY_MOD_INT_ASSIGN_VECTOR
#define FFT_POLY_MOD_INT_CONSTRUCT
#define FFT_POLY_MOD_INT_INV_INLINE
#define FFT_POLY_MOD_INT_MUL_INLINE
#define FFT_POLY_MOD_INT_ONLINE_INLINE
#define FFT_POLY_MOD_INT_RECURRENCE
#define FFT_POLY_MOD_INT_SHRINK
#define FFT_POLY_MOD_INT_SUB
#define FFT_POLY_MOD_INT_TRUNCATE
#endif

#ifdef FFT_POLY_MOD_INT_INV_INLINE
#define FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_SUB_INLINE
#define _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
#define _FFT_POLY_MOD_INT_INV
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE
#define FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#define _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
#define FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT
#endif

#ifdef FFT_POLY_MOD_INT_RECURRENCE
#define FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#define FFT_POLY_MOD_INT_INV_INLINE
#define FFT_POLY_MOD_INT_MUL_INLINE
#define FFT_POLY_MOD_INT_TRUNCATE
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE_INLINE
#define MOD_INT_SUB_INLINE
#define _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
#define _FFT_POLY_MOD_INT_INV
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
#include "math/fft/fft_online_mod_utils_macros.h"
#endif

#ifdef _FFT_POLY_MOD_INT_FFT_MUL_MOD_UTILS
#include "math/fft/fft_mul_mod_utils_macros.h"
#endif

#include "math/mod/mod_int_macros.h"
