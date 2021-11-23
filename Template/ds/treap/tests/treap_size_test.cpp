#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_size.h"

namespace ds {

TEST(TreapSizeTest, basic) {
  TreapSize<int> treap;
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(19));
  EXPECT_EQ(0, treap.calcPrefix(20));

  treap.update(10, true);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(1, treap.calcPrefix(20));

  treap.update(20, true);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(2, treap.calcPrefix(20));

  treap.update(15, false);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(2, treap.calcPrefix(20));

  treap.update(10, false);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(19));
  EXPECT_EQ(1, treap.calcPrefix(20));

  treap.update(5, true);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(1, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(2, treap.calcPrefix(20));

  treap.update(-5, true);
  EXPECT_EQ(1, treap.calcPrefix(0));
  EXPECT_EQ(2, treap.calcPrefix(9));
  EXPECT_EQ(2, treap.calcPrefix(10));
  EXPECT_EQ(2, treap.calcPrefix(19));
  EXPECT_EQ(3, treap.calcPrefix(20));

  treap.erase(10);
  EXPECT_EQ(1, treap.calcPrefix(0));
  EXPECT_EQ(2, treap.calcPrefix(9));
  EXPECT_EQ(2, treap.calcPrefix(10));
  EXPECT_EQ(2, treap.calcPrefix(19));
  EXPECT_EQ(3, treap.calcPrefix(20));

  treap.erase(-5);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(1, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(2, treap.calcPrefix(20));

  treap.erase(5);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(19));
  EXPECT_EQ(1, treap.calcPrefix(20));
}

TEST(TreapSizeTest, forest) {
  TreapSize<int> treap;

  treap.initRoots(3);
  EXPECT_EQ(0, treap.calcPrefix(0, 0));
  EXPECT_EQ(0, treap.calcPrefix(5, 0));
  EXPECT_EQ(0, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(0, treap.calcPrefix(5, 1));
  EXPECT_EQ(0, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(0, treap.calcPrefix(10, 2));

  treap.update(5, true, 1);
  EXPECT_EQ(0, treap.calcPrefix(0, 0));
  EXPECT_EQ(0, treap.calcPrefix(5, 0));
  EXPECT_EQ(0, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(1, treap.calcPrefix(5, 1));
  EXPECT_EQ(1, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(0, treap.calcPrefix(10, 2));

  treap.update(10, true, 2);
  EXPECT_EQ(0, treap.calcPrefix(0, 0));
  EXPECT_EQ(0, treap.calcPrefix(5, 0));
  EXPECT_EQ(0, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(1, treap.calcPrefix(5, 1));
  EXPECT_EQ(1, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(1, treap.calcPrefix(10, 2));

  treap.update(0, true, 0);
  EXPECT_EQ(1, treap.calcPrefix(0, 0));
  EXPECT_EQ(1, treap.calcPrefix(5, 0));
  EXPECT_EQ(1, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(1, treap.calcPrefix(5, 1));
  EXPECT_EQ(1, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(1, treap.calcPrefix(10, 2));

  treap.update(5, true, 0);
  EXPECT_EQ(1, treap.calcPrefix(0, 0));
  EXPECT_EQ(2, treap.calcPrefix(5, 0));
  EXPECT_EQ(2, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(1, treap.calcPrefix(5, 1));
  EXPECT_EQ(1, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(1, treap.calcPrefix(10, 2));

  treap.erase(5, 1);
  EXPECT_EQ(1, treap.calcPrefix(0, 0));
  EXPECT_EQ(2, treap.calcPrefix(5, 0));
  EXPECT_EQ(2, treap.calcPrefix(10, 0));
  EXPECT_EQ(0, treap.calcPrefix(0, 1));
  EXPECT_EQ(0, treap.calcPrefix(5, 1));
  EXPECT_EQ(0, treap.calcPrefix(10, 1));
  EXPECT_EQ(0, treap.calcPrefix(0, 2));
  EXPECT_EQ(0, treap.calcPrefix(5, 2));
  EXPECT_EQ(1, treap.calcPrefix(10, 2));
}

} // namespace ds
