#ifdef FFT_UTILS_ALL
#define FFT_UTILS_MUL_BIGINT
#define FFT_UTILS_MUL_COMPLEX_VECTOR
#define FFT_UTILS_MUL_INT
#endif

#ifdef FFT_UTILS_MUL_BIGINT
#define BIGINT_ASSIGN_COMPLEX_VECTOR
#define FFT_UTILS_MUL_INT
#endif

#ifdef FFT_UTILS_MUL_INT
#define COMPLEX_CONJ
#define COMPLEX_INIT_CONJ
#define COMPLEX_MUL
#define COMPLEX_SUB
#define _FFT_UTILS_COMPLEX_2
#endif

#ifdef FFT_UTILS_MUL_COMPLEX_VECTOR
#define _FFT_UTILS_COMPLEX_VECTOR_3
#endif

#define COMPLEX_ADD_INLINE
#define COMPLEX_DIV_INLINE_DOUBLE
#define COMPLEX_INIT
#define COMPLEX_INIT_MUL
#define COMPLEX_INIT_POLAR
#define COMPLEX_INIT_SUB
#define COMPLEX_MUL_INLINE

#include "math/bigint/bigint_macros.h"
#include "math/complex/complex_macros.h"
