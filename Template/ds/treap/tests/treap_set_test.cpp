#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_set.h"

namespace ds {

TEST(TreapSetTest, basic) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(19));
  EXPECT_EQ(0, treap.calcPrefix(20));

  treap.insert(10);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(0, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(1, treap.calcPrefix(20));

  treap.insert(20);
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

  treap.insert(5);
  EXPECT_EQ(0, treap.calcPrefix(0));
  EXPECT_EQ(1, treap.calcPrefix(9));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(19));
  EXPECT_EQ(2, treap.calcPrefix(20));

  treap.insert(-5);
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

TEST(TreapSetTest, initItems) {
  TreapSet<int> treap;
  treap.initItems({{5, true}, {10, true}, {11, true}});
  EXPECT_EQ(0, treap.calcPrefix(4));
  EXPECT_EQ(1, treap.calcPrefix(5));
  EXPECT_EQ(1, treap.calcPrefix(6));
  EXPECT_EQ(1, treap.calcPrefix(9));
  EXPECT_EQ(2, treap.calcPrefix(10));
  EXPECT_EQ(3, treap.calcPrefix(11));
  EXPECT_EQ(3, treap.calcPrefix(12));
}

} // namespace ds
