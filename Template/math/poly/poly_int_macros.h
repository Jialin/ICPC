#ifdef POLY_INT_ALL
#define POLY_INT_ASSIGN_VECTOR
#define POLY_INT_MUL
#define POLY_INT_MUL_INLINE
#endif

#ifdef POLY_INT_MUL
#define FFT_UTILS_MUL_INT
#endif

#ifdef POLY_INT_MUL_INLINE
#define FFT_UTILS_MUL_INLINE_INT
#endif

#if defined(POLY_INT_MUL) || defined(POLY_INT_MUL_INLINE)
#define _POLY_INT_FFT_UTILS
#endif

#include "math/fft/fft_mixed_utils_macros.h"
