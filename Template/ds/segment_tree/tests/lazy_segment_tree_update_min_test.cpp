#include "gtest/gtest.h"

#define BASE_LAZY_SEGMENT_TREE_ALL
#include "ds/segment_tree/base_lazy_segment_tree_macros.h"

#include "ds/segment_tree/lazy_segment_tree_update_min.h"

namespace ds {

TEST(LazySegmentTreeUpdateMin, basic) {
  LazySegmentTreeUpdateMin<int> st;
  st.init(vector<int>{3, 2, 1, 4, 5});
  EXPECT_EQ(2, st.calcRange(1, 2));
  EXPECT_EQ(1, st.calcRange(0, 3));
  EXPECT_EQ(4, st.calcRange(3, 5));
  EXPECT_EQ(4, st.calcRange(3, 4));
  EXPECT_EQ(5, st.calcRange(4, 5));

  st.updateRange(0, 5, 10);
  EXPECT_EQ(12, st.calcRange(1, 2));
  EXPECT_EQ(11, st.calcRange(0, 3));
  EXPECT_EQ(14, st.calcRange(3, 5));
  EXPECT_EQ(14, st.calcRange(3, 4));
  EXPECT_EQ(15, st.calcRange(4, 5));

  st.updateRange(2, 4, 100);
  EXPECT_EQ(12, st.calcRange(1, 2));
  EXPECT_EQ(12, st.calcRange(0, 3));
  EXPECT_EQ(15, st.calcRange(3, 5));
  EXPECT_EQ(114, st.calcRange(3, 4));
  EXPECT_EQ(15, st.calcRange(4, 5));

  st.updateRange(4, 5, 1000);
  EXPECT_EQ(12, st.calcRange(1, 2));
  EXPECT_EQ(12, st.calcRange(0, 3));
  EXPECT_EQ(114, st.calcRange(3, 5));
  EXPECT_EQ(114, st.calcRange(3, 4));
  EXPECT_EQ(1015, st.calcRange(4, 5));
}

} // namespace ds
