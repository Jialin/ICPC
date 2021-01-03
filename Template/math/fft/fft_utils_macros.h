#ifdef FFT_UTILS_ALL
#define FFT_UTILS_FFT_COMPLEX_MATRIX
#define FFT_UTILS_MUL_COMPLEX_VECTOR
#define FFT_UTILS_MUL_INLINE_COMPLEX_MATRIX
#define FFT_UTILS_MUL_INLINE_COMPLEX_VECTOR
#define FFT_UTILS_MUL_INLINE_INT
#define FFT_UTILS_MUL_INLINE_MOD
#define FFT_UTILS_MUL_INT
#define FFT_UTILS_ONLINE_MOD
#define FFT_UTILS_ONLINE_MOD_INT
#endif

#ifdef FFT_UTILS_MUL_INLINE_INT
#define FFT_UTILS_MUL_INT
#define _FFT_UTILS_SHRINK_INT_VECTOR
#endif

#ifdef FFT_UTILS_ONLINE_MOD
#define FFT_UTILS_ONLINE_MOD_INT
#endif

#ifdef FFT_UTILS_MUL_INLINE_COMPLEX_MATRIX
#define FFT_UTILS_FFT_COMPLEX_MATRIX
#endif

#ifdef FFT_UTILS_MUL_INT
#define COMPLEX_CONJ
#define COMPLEX_INIT_CONJ
#define COMPLEX_SUB
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
#define _FFT_UTILS_COMPLEX_VECTOR_3
#endif

#if defined(FFT_UTILS_MUL_COMPLEX_VECTOR) ||                                   \
    defined(FFT_UTILS_MUL_INLINE_COMPLEX_VECTOR) || defined(FFT_UTILS_MUL_INT)
#define _FFT_UTILS_SHRINK_COMPLEX_VECTOR
#endif

#ifdef FFT_UTILS_ONLINE_MOD_INT
#define FFT_UTILS_MUL_INLINE_MOD
#define _FFT_UTILS_EXPAND_INT_VECTOR
#endif

#ifdef FFT_UTILS_MUL_INLINE_MOD
#define COMPLEX_ADD
#define COMPLEX_CONJ
#define COMPLEX_SUB
#define _FFT_UTILS_EXPAND_INT_VECTOR
#define _FFT_UTILS_SHRINK_INT_VECTOR
#endif

#if defined(FFT_UTILS_MUL_INLINE_COMPLEX_MATRIX) ||                            \
    defined(FFT_UTILS_MUL_INLINE_COMPLEX_VECTOR)
#define COMPLEX_MUL_INLINE
#endif

#define COMPLEX_ADD_INLINE
#define COMPLEX_DIV_INLINE_DOUBLE
#define COMPLEX_INIT
#define COMPLEX_INIT_POLAR
#define COMPLEX_INIT_SUB
#define COMPLEX_MUL

#include "math/complex/complex_macros.h"
