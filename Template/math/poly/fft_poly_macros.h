#ifdef FFT_POLY_ALL
#define FFT_POLY_ASSIGN
#define FFT_POLY_ASSIGN_VECTOR
#define FFT_POLY_CONSTRUCT
#define FFT_POLY_MUL_INLINE
#define FFT_POLY_MUL_INLINE_CYCLIC
#endif

#ifdef FFT_POLY_MUL_INLINE
#define FFT_MUL_UTILS_MUL_INLINE_REAL
#endif

#ifdef FFT_POLY_MUL_INLINE_CYCLIC
#define FFT_MUL_UTILS_MUL_INLINE_REAL
#endif

#include "math/fft/fft_mul_utils_macros.h"
