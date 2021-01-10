#ifdef MOD_INT_ALL
#define MOD_INT_ADD
#define MOD_INT_ADD_INLINE
#define MOD_INT_ASSIGN
#define MOD_INT_DIV
#define MOD_INT_DIV_INLINE
#define MOD_INT_EXP
#define MOD_INT_FLIP
#define MOD_INT_INV
#define MOD_INT_INV_INLINE
#define MOD_INT_MUL
#define MOD_INT_MUL_INLINE
#define MOD_INT_NEGATE
#define MOD_INT_NEGATE_INLINE
#define MOD_INT_SUB_INLINE
#endif

#ifdef MOD_INT_EXP
#define MOD_INT_INV
#define MOD_INT_MUL_INLINE
#endif

#ifdef MOD_INT_DIV
#define MOD_INT_INV
#define MOD_INT_MUL
#endif
