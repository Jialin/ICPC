#ifdef FFT_MUL_UTILS_ALL
#define FFT_MUL_UTILS_MUL_INLINE_INT
#define FFT_MUL_UTILS_MUL_INT
#endif

#define COMPLEX_CONJ
#define COMPLEX_DIV_INLINE_DOUBLE
#define COMPLEX_INIT
#define COMPLEX_INIT_CONJ
#define COMPLEX_SUB

#ifdef FFT_MUL_UTILS_MUL_INT
#define _FFT_UTILS_SHRINK_COMPLEX_VECTOR
#endif

#include "math/complex/complex_macros.h"
#include "math/fft/fft_utils_macros.h"
