#ifdef BASE_SEGMENT_TREE_ALL
#define BASE_SEGMENT_TREE_CALC_RANGE
#define BASE_SEGMENT_TREE_INIT
#define BASE_SEGMENT_TREE_RESERVE
#define BASE_SEGMENT_TREE_UPDATE
#define _BASE_SEGMENT_TREE_APPEND_V
#define _BASE_SEGMENT_TREE_CALC_RANGE
#define _BASE_SEGMENT_TREE_CLEAR_V
#define _BASE_SEGMENT_TREE_INIT
#define _BASE_SEGMENT_TREE_UPDATE
#define _BASE_SEGMENT_TREE_UPDATE_V
#endif

#ifdef BASE_SEGMENT_TREE_CALC_RANGE
#define _BASE_SEGMENT_TREE_APPEND_V
#define _BASE_SEGMENT_TREE_CALC_RANGE
#define _BASE_SEGMENT_TREE_CLEAR_V
#endif

#ifdef BASE_SEGMENT_TREE_INIT
#define _BASE_SEGMENT_TREE_INIT
#endif

#ifdef BASE_SEGMENT_TREE_UPDATE
#define _BASE_SEGMENT_TREE_UPDATE
#define _BASE_SEGMENT_TREE_UPDATE_V
#endif

#ifdef _BASE_SEGMENT_TREE_CALC_RANGE
#define _BASE_SEGMENT_TREE_APPEND_V
#endif

#ifdef _BASE_SEGMENT_TREE_UPDATE
#define _BASE_SEGMENT_TREE_UPDATE_V
#endif
