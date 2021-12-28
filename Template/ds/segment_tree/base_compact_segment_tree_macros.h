#ifdef BASE_COMPACT_SEGMENT_TREE_ALL
#define BASE_COMPACT_SEGMENT_TREE_INIT
#define BASE_COMPACT_SEGMENT_TREE_RESERVE
#define BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define BASE_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_APPEND_V
#define _BASE_COMPACT_SEGMENT_TREE_APPLY_UPDATE_WRAPPER
#define _BASE_COMPACT_SEGMENT_TREE_CLEAR_V
#define _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER
#endif

#ifdef BASE_COMPACT_SEGMENT_TREE_UPDATE_RANGE
#define _BASE_COMPACT_SEGMENT_TREE_APPLY_UPDATE_WRAPPER
#endif

#ifdef _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_WRAPPER
#define _BASE_COMPACT_SEGMENT_TREE_TRAVERSE_RANGE
#endif
