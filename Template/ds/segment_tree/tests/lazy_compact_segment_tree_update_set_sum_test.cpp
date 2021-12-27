#include "gtest/gtest.h"

#define BASE_LAZY_COMPACT_SEGMENT_TREE_ALL
#include "ds/segment_tree/base_lazy_compact_segment_tree_macros.h"

#include "ds/segment_tree/lazy_compact_segment_tree_update_set_sum.h"

namespace ds {

TEST(LazyCompactSegmentTreeUpdateSetSum, basic) {
  LazyCompactSegmentTreeUpdateSetSum<int64_t, int> st;
  st.init(vector<int>{2, 3, 1, 1, 5, 3});
  EXPECT_EQ(7, st.calcRange(2, 5));

  st.updateRange(1, 4, 2);
  EXPECT_EQ(11, st.calcRange(2, 5));

  st.setRange(1, 4, 5);
  EXPECT_EQ(15, st.calcRange(2, 5));
}

} // namespace ds
