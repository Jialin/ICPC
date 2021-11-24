#ifdef BASE_TREAP_ALL
#define BASE_TREAP_CALC_KTH
#define BASE_TREAP_CALC_PREFIX
#define BASE_TREAP_CALC_RANGE
#define BASE_TREAP_CALC_SUFFIX
#define BASE_TREAP_ERASE
#define BASE_TREAP_INIT_ORDERED_ITEMS
#define BASE_TREAP_RESERVE_NODES
#define BASE_TREAP_UPDATE
#define _BASE_TREAP_CALC_KTH
#define _BASE_TREAP_CALC_PREFIX
#define _BASE_TREAP_CALC_RANGE
#define _BASE_TREAP_CALC_SUFFIX
#define _BASE_TREAP_ERASE
#define _BASE_TREAP_INIT_ORDERED_ITEMS
#define _BASE_TREAP_MERGE
#define _BASE_TREAP_NEW_NODE
#define _BASE_TREAP_ROTATE
#define _BASE_TREAP_UPDATE
#endif

#ifdef BASE_TREAP_CALC_KTH
#define _BASE_TREAP_CALC_KTH
#endif

#ifdef BASE_TREAP_CALC_PREFIX
#define _BASE_TREAP_CALC_PREFIX
#endif

#ifdef BASE_TREAP_CALC_RANGE
#define _BASE_TREAP_CALC_RANGE
#define _BASE_TREAP_CALC_SUFFIX
#define _BASE_TREAP_MERGE
#endif

#ifdef BASE_TREAP_CALC_SUFFIX
#define _BASE_TREAP_CALC_SUFFIX
#endif

#ifdef BASE_TREAP_ERASE
#define _BASE_TREAP_ERASE
#define _BASE_TREAP_MERGE
#endif

#ifdef BASE_TREAP_INIT_ITEMS
#define _BASE_TREAP_NEW_NODE
#define _BASE_TREAP_ROTATE
#endif

#ifdef BASE_TREAP_INIT_ORDERED_ITEMS
#define _BASE_TREAP_INIT_ORDERED_ITEMS
#endif

#ifdef BASE_TREAP_UPDATE
#define _BASE_TREAP_NEW_NODE
#define _BASE_TREAP_ROTATE
#define _BASE_TREAP_UPDATE
#endif

#ifdef _BASE_TREAP_CALC_RANGE
#define _BASE_TREAP_CALC_SUFFIX
#define _BASE_TREAP_MERGE
#endif

#ifdef _BASE_TREAP_ERASE
#define _BASE_TREAP_MERGE
#endif

#ifdef _BASE_TREAP_UPDATE
#define _BASE_TREAP_NEW_NODE
#define _BASE_TREAP_ROTATE
#endif
