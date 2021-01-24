#ifdef FFT_POLY_MOD_INT_ALL
#define FFT_POLY_MOD_INT_ASSIGN_VECTOR
#define FFT_POLY_MOD_INT_CONSTRUCT
#define FFT_POLY_MOD_INT_MUL_INLINE
#define FFT_POLY_MOD_INT_ONLINE_INLINE
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE
#define FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
#define FFT_ONLINE_MOD_UTILS_ONLINE_INLINE_MOD_INT
#endif

#ifdef FFT_POLY_MOD_INT_MUL_INLINE
#include "math/fft/fft_mul_mod_utils_macros.h"
#endif

#ifdef FFT_POLY_MOD_INT_ONLINE_INLINE
#include "math/fft/fft_online_mod_utils_macros.h"
#endif

#include "math/mod/mod_int_macros.h"
