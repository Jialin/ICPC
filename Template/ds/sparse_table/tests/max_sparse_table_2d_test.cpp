#include "gtest/gtest.h"

#include "ds/sparse_table/max_sparse_table_2d.h"

namespace ds {

TEST(MaxSparseTable2DTest, basic) {
  MaxSparseTable2D<int> st;
  st.init({{4, 2, 3, 1}, {1, 1, 3, 2}, {1, 2, 3, 4}});
  EXPECT_EQ(4, st.calc(0, 0, 1, 1));
  EXPECT_EQ(4, st.calc(0, 0, 1, 2));
  EXPECT_EQ(4, st.calc(0, 0, 1, 3));
  EXPECT_EQ(4, st.calc(0, 0, 1, 4));
  EXPECT_EQ(4, st.calc(0, 0, 2, 1));
  EXPECT_EQ(4, st.calc(0, 0, 2, 2));
  EXPECT_EQ(4, st.calc(0, 0, 2, 3));
  EXPECT_EQ(4, st.calc(0, 0, 2, 4));
  EXPECT_EQ(4, st.calc(0, 0, 3, 1));
  EXPECT_EQ(4, st.calc(0, 0, 3, 2));
  EXPECT_EQ(4, st.calc(0, 0, 3, 3));
  EXPECT_EQ(4, st.calc(0, 0, 3, 4));

  EXPECT_EQ(2, st.calc(0, 1, 1, 2));
  EXPECT_EQ(3, st.calc(0, 1, 1, 3));
  EXPECT_EQ(3, st.calc(0, 1, 1, 4));
  EXPECT_EQ(2, st.calc(0, 1, 2, 2));
  EXPECT_EQ(3, st.calc(0, 1, 2, 3));
  EXPECT_EQ(3, st.calc(0, 1, 2, 4));
  EXPECT_EQ(2, st.calc(0, 1, 3, 2));
  EXPECT_EQ(3, st.calc(0, 1, 3, 3));
  EXPECT_EQ(4, st.calc(0, 1, 3, 4));

  EXPECT_EQ(3, st.calc(0, 2, 1, 3));
  EXPECT_EQ(3, st.calc(0, 2, 1, 4));
  EXPECT_EQ(3, st.calc(0, 2, 2, 3));
  EXPECT_EQ(3, st.calc(0, 2, 2, 4));
  EXPECT_EQ(3, st.calc(0, 2, 3, 3));
  EXPECT_EQ(4, st.calc(0, 2, 3, 4));

  EXPECT_EQ(1, st.calc(0, 3, 1, 4));
  EXPECT_EQ(2, st.calc(0, 3, 2, 4));
  EXPECT_EQ(4, st.calc(0, 3, 3, 4));

  EXPECT_EQ(1, st.calc(1, 0, 2, 1));
  EXPECT_EQ(1, st.calc(1, 0, 2, 2));
  EXPECT_EQ(3, st.calc(1, 0, 2, 3));
  EXPECT_EQ(3, st.calc(1, 0, 2, 4));
  EXPECT_EQ(1, st.calc(1, 0, 3, 1));
  EXPECT_EQ(2, st.calc(1, 0, 3, 2));
  EXPECT_EQ(3, st.calc(1, 0, 3, 3));
  EXPECT_EQ(4, st.calc(1, 0, 3, 4));

  EXPECT_EQ(1, st.calc(1, 1, 2, 2));
  EXPECT_EQ(3, st.calc(1, 1, 2, 3));
  EXPECT_EQ(3, st.calc(1, 1, 2, 4));
  EXPECT_EQ(2, st.calc(1, 1, 3, 2));
  EXPECT_EQ(3, st.calc(1, 1, 3, 3));
  EXPECT_EQ(4, st.calc(1, 1, 3, 4));

  EXPECT_EQ(3, st.calc(1, 2, 2, 3));
  EXPECT_EQ(3, st.calc(1, 2, 2, 4));
  EXPECT_EQ(3, st.calc(1, 2, 3, 3));
  EXPECT_EQ(4, st.calc(1, 2, 3, 4));

  EXPECT_EQ(2, st.calc(1, 3, 2, 4));
  EXPECT_EQ(4, st.calc(1, 3, 3, 4));

  EXPECT_EQ(1, st.calc(2, 0, 3, 1));
  EXPECT_EQ(2, st.calc(2, 0, 3, 2));
  EXPECT_EQ(3, st.calc(2, 0, 3, 3));
  EXPECT_EQ(4, st.calc(2, 0, 3, 4));

  EXPECT_EQ(2, st.calc(2, 1, 3, 2));
  EXPECT_EQ(3, st.calc(2, 1, 3, 3));
  EXPECT_EQ(4, st.calc(2, 1, 3, 4));

  EXPECT_EQ(3, st.calc(2, 2, 3, 3));
  EXPECT_EQ(4, st.calc(2, 2, 3, 4));

  EXPECT_EQ(4, st.calc(2, 3, 3, 4));
}

} // namespace ds
