#ifdef BASE_FENWICK_ALL
#define BASE_FENWICK_CALC_KTH
#define BASE_FENWICK_CALC_PREFIX
#define BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_RESERVE
#define _BASE_FENWICK_CALC_PREFIX
#define _BASE_FENWICK_SUB_V
#endif

#ifdef BASE_FENWICK_CALC_KTH
#define _BASE_FENWICK_SUB_V
#endif

#ifdef BASE_FENWICK_CALC_PREFIX
#define _BASE_FENWICK_CALC_PREFIX
#endif

#ifdef BASE_FENWICK_CALC_RANGE
#define BASE_FENWICK_CALC_PREFIX
#define _BASE_FENWICK_CALC_PREFIX
#define _BASE_FENWICK_SUB_V
#endif
