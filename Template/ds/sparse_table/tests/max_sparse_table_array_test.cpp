#include "gtest/gtest.h"

#define BASE_SPARSE_TABLE_ARRAY_ALL
#include "ds/sparse_table/base_sparse_table_array_macros.h"

#include "ds/sparse_table/max_sparse_table_array.h"

namespace ds {

TEST(MaxSparseTableTest, basic) {
  MaxSparseTableArray<int, 3, 5> st;
  st.init({3, 2, 1, 4, 5});

  EXPECT_EQ(3, st.calc(0, 1));
  EXPECT_EQ(2, st.calc(1, 2));
  EXPECT_EQ(1, st.calc(2, 3));
  EXPECT_EQ(4, st.calc(3, 4));
  EXPECT_EQ(5, st.calc(4, 5));

  EXPECT_EQ(3, st.calc(0, 2));
  EXPECT_EQ(2, st.calc(1, 3));
  EXPECT_EQ(4, st.calc(2, 4));
  EXPECT_EQ(5, st.calc(3, 5));

  EXPECT_EQ(3, st.calc(0, 3));
  EXPECT_EQ(4, st.calc(1, 4));
  EXPECT_EQ(5, st.calc(2, 5));

  EXPECT_EQ(4, st.calc(0, 4));
  EXPECT_EQ(5, st.calc(1, 5));

  EXPECT_EQ(5, st.calc(0, 5));
}

} // namespace ds
