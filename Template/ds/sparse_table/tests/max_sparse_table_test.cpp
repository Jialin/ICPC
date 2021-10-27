#include "gtest/gtest.h"

#define BASE_SPARSE_TABLE_ALL
#include "ds/sparse_table/base_sparse_table_macros.h"

#include "ds/sparse_table/max_sparse_table.h"

namespace ds {

TEST(MaxSparseTableTest, basic) {
  MaxSparseTable<int> maxST;
  maxST.init({3, 2, 1, 4, 5});
  int res;

  maxST.calc(0, 1, res);
  EXPECT_EQ(3, res);
  maxST.calc(1, 2, res);
  EXPECT_EQ(2, res);
  maxST.calc(2, 3, res);
  EXPECT_EQ(1, res);
  maxST.calc(3, 4, res);
  EXPECT_EQ(4, res);
  maxST.calc(4, 5, res);
  EXPECT_EQ(5, res);

  maxST.calc(0, 2, res);
  EXPECT_EQ(3, res);
  maxST.calc(1, 3, res);
  EXPECT_EQ(2, res);
  maxST.calc(2, 4, res);
  EXPECT_EQ(4, res);
  maxST.calc(3, 5, res);
  EXPECT_EQ(5, res);

  maxST.calc(0, 3, res);
  EXPECT_EQ(3, res);
  maxST.calc(1, 4, res);
  EXPECT_EQ(4, res);
  maxST.calc(2, 5, res);
  EXPECT_EQ(5, res);

  maxST.calc(0, 4, res);
  EXPECT_EQ(4, res);
  maxST.calc(1, 5, res);
  EXPECT_EQ(5, res);

  maxST.calc(0, 5, res);
  EXPECT_EQ(5, res);
}

} // namespace ds
