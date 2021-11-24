#include "gtest/gtest.h"

#define BASE_TREAP_FOREST_ALL
#define TREAP_FOREST_SET_ALL
#include "ds/treap/base_treap_forest_macros.h"
#include "ds/treap/treap_forest_set_macros.h"

#include "ds/treap/treap_forest_set.h"

namespace ds {

TEST(TreapForestSetTest, basic) {
  TreapForestSet<int> forest;

  forest.init(3);
  EXPECT_EQ(0, forest.calcPrefix(1, 0));
  EXPECT_EQ(0, forest.calcPrefix(6, 0));
  EXPECT_EQ(0, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(0, forest.calcPrefix(6, 1));
  EXPECT_EQ(0, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(0, forest.calcPrefix(11, 2));

  forest.insert(5, 1);
  EXPECT_EQ(0, forest.calcPrefix(1, 0));
  EXPECT_EQ(0, forest.calcPrefix(6, 0));
  EXPECT_EQ(0, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(1, forest.calcPrefix(6, 1));
  EXPECT_EQ(1, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(0, forest.calcPrefix(11, 2));

  forest.insert(10, 2);
  EXPECT_EQ(0, forest.calcPrefix(1, 0));
  EXPECT_EQ(0, forest.calcPrefix(6, 0));
  EXPECT_EQ(0, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(1, forest.calcPrefix(6, 1));
  EXPECT_EQ(1, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(1, forest.calcPrefix(11, 2));

  forest.insert(0, 0);
  EXPECT_EQ(1, forest.calcPrefix(1, 0));
  EXPECT_EQ(1, forest.calcPrefix(6, 0));
  EXPECT_EQ(1, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(1, forest.calcPrefix(6, 1));
  EXPECT_EQ(1, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(1, forest.calcPrefix(11, 2));

  forest.insert(5, 0);
  EXPECT_EQ(1, forest.calcPrefix(1, 0));
  EXPECT_EQ(2, forest.calcPrefix(6, 0));
  EXPECT_EQ(2, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(1, forest.calcPrefix(6, 1));
  EXPECT_EQ(1, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(1, forest.calcPrefix(11, 2));

  forest.erase(5, 1);
  EXPECT_EQ(1, forest.calcPrefix(1, 0));
  EXPECT_EQ(2, forest.calcPrefix(6, 0));
  EXPECT_EQ(2, forest.calcPrefix(11, 0));
  EXPECT_EQ(0, forest.calcPrefix(1, 1));
  EXPECT_EQ(0, forest.calcPrefix(6, 1));
  EXPECT_EQ(0, forest.calcPrefix(11, 1));
  EXPECT_EQ(0, forest.calcPrefix(1, 2));
  EXPECT_EQ(0, forest.calcPrefix(6, 2));
  EXPECT_EQ(1, forest.calcPrefix(11, 2));
}

} // namespace ds
