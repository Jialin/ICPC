#ifdef POLY_INT_ALL
#define POLY_INT_ACCESS
#define POLY_INT_ASSIGN
#define POLY_INT_CONSTRUCT
#define POLY_INT_CYCLIC_MUL_INLINE
#define POLY_INT_MUL_INLINE
#define POLY_INT_RESERVE
#define POLY_INT_RESIZE
#define POLY_INT_SIZE
#endif

#ifdef POLY_INT_MUL_INLINE
#define FFT_UTILS_MUL_INLINE_INT
#define _POLY_INT_FFT_UTILS
#endif

#include "math/fft/fft_utils_macros.h"
