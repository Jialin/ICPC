#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_sum.h"

namespace ds {

TEST(TreapSumTest, basic) {
  TreapSum<int> treap;
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(19));
  EXPECT_EQ(0, treap.calcPrefix(20));

  treap.update(10, 100);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(100, treap.calcPrefix(10));
  EXPECT_EQ(100, treap.calcPrefix(19));
  EXPECT_EQ(100, treap.calcPrefix(20));

  treap.update(20, 200);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(100, treap.calcPrefix(10));
  EXPECT_EQ(100, treap.calcPrefix(19));
  EXPECT_EQ(300, treap.calcPrefix(20));

  treap.update(5, 300);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(300, treap.calcPrefix(9));
  EXPECT_EQ(400, treap.calcPrefix(10));
  EXPECT_EQ(400, treap.calcPrefix(19));
  EXPECT_EQ(600, treap.calcPrefix(20));

  treap.update(-5, 400);
  EXPECT_EQ(400, treap.calcPrefix(0));
  EXPECT_EQ(700, treap.calcPrefix(9));
  EXPECT_EQ(800, treap.calcPrefix(10));
  EXPECT_EQ(800, treap.calcPrefix(19));
  EXPECT_EQ(1000, treap.calcPrefix(20));
}

} // namespace ds
