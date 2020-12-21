#ifdef BIGINT_ALL
#define BIGINT_ADD
#define BIGINT_ADD_INLINE
#define BIGINT_ADD_INLINE_INT
#define BIGINT_ADD_INT
#define BIGINT_ASSIGN
#define BIGINT_ASSIGN_CHAR_ARRAY
#define BIGINT_ASSIGN_COMPLEX_VECTOR
#define BIGINT_ASSIGN_INT
#define BIGINT_ASSIGN_STRING
#define BIGINT_CLEAN
#define BIGINT_CMP
#define BIGINT_CMP_INT
#define BIGINT_CONSTRUCT_EMPTY
#define BIGINT_CONSTRUCT_INT
#define BIGINT_DIGIT_COUNT
#define BIGINT_DIGIT_SUM
#define BIGINT_DIV_INLINE
#define BIGINT_DIV_INLINE_INT
#define BIGINT_DIV_MOD_INLINE_INT
#define BIGINT_EQ_INT
#define BIGINT_GCD_INLINE
#define BIGINT_GE
#define BIGINT_GE_INT
#define BIGINT_GT_INT
#define BIGINT_INIT_ADD
#define BIGINT_INIT_CAPACITY
#define BIGINT_INIT_CHAR_ARRAY
#define BIGINT_INIT_INT
#define BIGINT_INIT_MUL
#define BIGINT_LT
#define BIGINT_LT_INT
#define BIGINT_MOD_DIV_INLINE
#define BIGINT_MOD_INLINE
#define BIGINT_MOD_INT
#define BIGINT_MUL
#define BIGINT_MUL_INLINE
#define BIGINT_MUL_INLINE_INT
#define BIGINT_MUL_INT
#define BIGINT_NE_INT
#define BIGINT_OUTPUT
#define BIGINT_OUTPUT_CHAR_ARRAY
#define BIGINT_OUTPUT_COMPLEX_VECTOR
#define BIGINT_OUTPUT_FAST
#define BIGINT_SUB
#define BIGINT_SUB_INLINE
#endif

#ifdef BIGINT_OUTPUT_COMPLEX_VECTOR
#define COMPLEX_INIT
#endif

#ifdef BIGINT_SUB
#define BIGINT_SUB_INLINE
#endif

#ifdef BIGINT_ADD_INT
#define BIGINT_ADD_INLINE_INT
#endif

#if defined(BIGINT_GCD_INLINE) || defined(BIGINT_GE) || defined(BIGINT_LT)
#define BIGINT_CMP
#endif

#if defined(BIGINT_EQ_INT) || defined(BIGINT_GCD_INLINE) ||                    \
    defined(BIGINT_GE_INT) || defined(BIGINT_GT_INT) ||                        \
    defined(BIGINT_LT_INT) || defined(BIGINT_NE_INT)
#define BIGINT_CMP_INT
#endif

#if defined(BIGINT_GCD_INLINE) || defined(BIGINT_DIV_INLINE_INT)
#define BIGINT_DIV_MOD_INLINE_INT
#endif

#if defined(LOCAL) && defined(BIGINT_SUB_INLINE)
#define BIGINT_COMPARE
#endif

#ifdef BIGINT_MUL_INT
#define BIGINT_MUL_INLINE_INT
#endif

#ifdef BIGINT_ADD
#define BIGINT_INIT_ADD
#endif

#if defined(BIGINT_ADD_INT) || defined(BIGINT_INIT_ADD) ||                     \
    defined(BIGINT_MUL_INLINE) || defined(BIGINT_MUL_INT) ||                   \
    defined(BIGINT_SUB)
#define BIGINT_ASSIGN
#endif

#ifdef BIGINT_INIT_ADD
#define BIGINT_ADD_INLINE
#endif

#if defined(BIGINT_MUL) || defined(BIGINT_MUL_INLINE)
#define BIGINT_INIT_MUL
#endif

#if defined(BIGINT_ASSIGN_INT) || defined(BIGINT_CONSTRUCT_INT)
#define BIGINT_INIT_INT
#endif

#if defined(BIGINT_DIV_INLINE) || defined(BIGINT_MOD_INLINE)
#define BIGINT_MOD_DIV_INLINE
#endif

#if defined(BIGINT_ASSIGN_COMPLEX_VECTOR) ||                                   \
    defined(BIGINT_DIV_MOD_INLINE_INT) || defined(BIGINT_INIT_CHAR_ARRAY) ||   \
    defined(BIGINT_INIT_MUL) || defined(BIGINT_MOD_DIV_INLINE) ||              \
    defined(BIGINT_MUL_INLINE_INT) || defined(BIGINT_SUB_INLINE)
#define BIGINT_CLEAN
#endif

#if defined(BIGINT_ASSIGN_CHAR_ARRAY) || defined(BIGINT_ASSIGN_STRING)
#define BIGINT_INIT_CHAR_ARRAY
#endif

#include "math/complex/complex_macros.h"
