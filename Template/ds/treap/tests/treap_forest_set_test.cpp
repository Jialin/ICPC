#include "gtest/gtest.h"

#define BASE_TREAP_FOREST_ALL
#include "ds/treap/base_treap_forest_macros.h"

#include "ds/treap/treap_forest_set.h"

namespace ds {

TEST(TreapForestSetTest, basic) {
  TreapForestSet<int> forest;

  forest.init(3);
  EXPECT_EQ(0, forest.calcPrefix(0, 0));
  EXPECT_EQ(0, forest.calcPrefix(5, 0));
  EXPECT_EQ(0, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(0, forest.calcPrefix(5, 1));
  EXPECT_EQ(0, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(0, forest.calcPrefix(10, 2));

  forest.insert(5, 1);
  EXPECT_EQ(0, forest.calcPrefix(0, 0));
  EXPECT_EQ(0, forest.calcPrefix(5, 0));
  EXPECT_EQ(0, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(1, forest.calcPrefix(5, 1));
  EXPECT_EQ(1, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(0, forest.calcPrefix(10, 2));

  forest.insert(10, 2);
  EXPECT_EQ(0, forest.calcPrefix(0, 0));
  EXPECT_EQ(0, forest.calcPrefix(5, 0));
  EXPECT_EQ(0, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(1, forest.calcPrefix(5, 1));
  EXPECT_EQ(1, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(1, forest.calcPrefix(10, 2));

  forest.insert(0, 0);
  EXPECT_EQ(1, forest.calcPrefix(0, 0));
  EXPECT_EQ(1, forest.calcPrefix(5, 0));
  EXPECT_EQ(1, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(1, forest.calcPrefix(5, 1));
  EXPECT_EQ(1, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(1, forest.calcPrefix(10, 2));

  forest.insert(5, 0);
  EXPECT_EQ(1, forest.calcPrefix(0, 0));
  EXPECT_EQ(2, forest.calcPrefix(5, 0));
  EXPECT_EQ(2, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(1, forest.calcPrefix(5, 1));
  EXPECT_EQ(1, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(1, forest.calcPrefix(10, 2));

  forest.erase(5, 1);
  EXPECT_EQ(1, forest.calcPrefix(0, 0));
  EXPECT_EQ(2, forest.calcPrefix(5, 0));
  EXPECT_EQ(2, forest.calcPrefix(10, 0));
  EXPECT_EQ(0, forest.calcPrefix(0, 1));
  EXPECT_EQ(0, forest.calcPrefix(5, 1));
  EXPECT_EQ(0, forest.calcPrefix(10, 1));
  EXPECT_EQ(0, forest.calcPrefix(0, 2));
  EXPECT_EQ(0, forest.calcPrefix(5, 2));
  EXPECT_EQ(1, forest.calcPrefix(10, 2));
}

} // namespace ds
