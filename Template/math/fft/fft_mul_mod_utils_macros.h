#ifdef FFT_MUL_MOD_UTILS_ALL
#define FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#endif

#ifdef FFT_MUL_MOD_UTILS_MUL_INLINE_MOD_INT
#define COMPLEX_ADD
#define COMPLEX_CONJ
#define COMPLEX_SUB
#define MOD_INT_CONST_MOD
#define _FFT_MUL_MOD_UTILS_MOD_INT
#endif

#ifdef _FFT_MUL_MOD_UTILS_MOD_INT
#include "math/mod/mod_int_macros.h"
#endif

#include "math/fft/fft_utils_macros.h"
