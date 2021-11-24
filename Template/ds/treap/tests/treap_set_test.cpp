#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_set.h"

namespace ds {

TEST(TreapSetTest, calcPrefix) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(11));
  EXPECT_EQ(0, treap.calcPrefix(20));
  EXPECT_EQ(0, treap.calcPrefix(21));

  treap.insert(10);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(11));
  EXPECT_EQ(1, treap.calcPrefix(20));
  EXPECT_EQ(1, treap.calcPrefix(21));

  treap.insert(20);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(11));
  EXPECT_EQ(1, treap.calcPrefix(20));
  EXPECT_EQ(2, treap.calcPrefix(21));

  treap.erase(15);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(11));
  EXPECT_EQ(1, treap.calcPrefix(20));
  EXPECT_EQ(2, treap.calcPrefix(21));

  treap.erase(10);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(11));
  EXPECT_EQ(0, treap.calcPrefix(20));
  EXPECT_EQ(1, treap.calcPrefix(21));

  treap.insert(5);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(11));
  EXPECT_EQ(1, treap.calcPrefix(20));
  EXPECT_EQ(2, treap.calcPrefix(21));

  treap.insert(-5);
  EXPECT_EQ(1, treap.calcPrefix(1));
  EXPECT_EQ(2, treap.calcPrefix(10));
  EXPECT_EQ(2, treap.calcPrefix(11));
  EXPECT_EQ(2, treap.calcPrefix(20));
  EXPECT_EQ(3, treap.calcPrefix(21));

  treap.erase(10);
  EXPECT_EQ(1, treap.calcPrefix(1));
  EXPECT_EQ(2, treap.calcPrefix(10));
  EXPECT_EQ(2, treap.calcPrefix(11));
  EXPECT_EQ(2, treap.calcPrefix(20));
  EXPECT_EQ(3, treap.calcPrefix(21));

  treap.erase(-5);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(1, treap.calcPrefix(11));
  EXPECT_EQ(1, treap.calcPrefix(20));
  EXPECT_EQ(2, treap.calcPrefix(21));

  treap.erase(5);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(11));
  EXPECT_EQ(0, treap.calcPrefix(20));
  EXPECT_EQ(1, treap.calcPrefix(21));
}

TEST(TreapSetTest, calcSuffix) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.calcSuffix(0));
  EXPECT_EQ(0, treap.calcSuffix(9));
  EXPECT_EQ(0, treap.calcSuffix(10));
  EXPECT_EQ(0, treap.calcSuffix(19));
  EXPECT_EQ(0, treap.calcSuffix(20));

  treap.insert(10);
  EXPECT_EQ(1, treap.calcSuffix(0));
  EXPECT_EQ(1, treap.calcSuffix(9));
  EXPECT_EQ(1, treap.calcSuffix(10));
  EXPECT_EQ(0, treap.calcSuffix(19));
  EXPECT_EQ(0, treap.calcSuffix(20));

  treap.insert(20);
  EXPECT_EQ(2, treap.calcSuffix(0));
  EXPECT_EQ(2, treap.calcSuffix(9));
  EXPECT_EQ(2, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.insert(5);
  EXPECT_EQ(3, treap.calcSuffix(0));
  EXPECT_EQ(2, treap.calcSuffix(9));
  EXPECT_EQ(2, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.insert(-5);
  EXPECT_EQ(3, treap.calcSuffix(0));
  EXPECT_EQ(2, treap.calcSuffix(9));
  EXPECT_EQ(2, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.erase(10);
  EXPECT_EQ(2, treap.calcSuffix(0));
  EXPECT_EQ(1, treap.calcSuffix(9));
  EXPECT_EQ(1, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.erase(10);
  EXPECT_EQ(2, treap.calcSuffix(0));
  EXPECT_EQ(1, treap.calcSuffix(9));
  EXPECT_EQ(1, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.erase(-5);
  EXPECT_EQ(2, treap.calcSuffix(0));
  EXPECT_EQ(1, treap.calcSuffix(9));
  EXPECT_EQ(1, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));

  treap.erase(5);
  EXPECT_EQ(1, treap.calcSuffix(0));
  EXPECT_EQ(1, treap.calcSuffix(9));
  EXPECT_EQ(1, treap.calcSuffix(10));
  EXPECT_EQ(1, treap.calcSuffix(19));
  EXPECT_EQ(1, treap.calcSuffix(20));
}

TEST(TreapSetTest, calcRange) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.calcRange(0, 21));
  EXPECT_EQ(0, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(0, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(0, treap.calcRange(20, 21));

  treap.insert(10);
  EXPECT_EQ(1, treap.calcRange(0, 21));
  EXPECT_EQ(0, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(1, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(0, treap.calcRange(20, 21));

  treap.insert(20);
  EXPECT_EQ(2, treap.calcRange(0, 21));
  EXPECT_EQ(0, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(1, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.insert(5);
  EXPECT_EQ(3, treap.calcRange(0, 21));
  EXPECT_EQ(1, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(1, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.insert(-5);
  EXPECT_EQ(3, treap.calcRange(0, 21));
  EXPECT_EQ(1, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(1, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.erase(10);
  EXPECT_EQ(2, treap.calcRange(0, 21));
  EXPECT_EQ(1, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(0, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.erase(10);
  EXPECT_EQ(2, treap.calcRange(0, 21));
  EXPECT_EQ(1, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(0, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.erase(-5);
  EXPECT_EQ(2, treap.calcRange(0, 21));
  EXPECT_EQ(1, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(0, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));

  treap.erase(5);
  EXPECT_EQ(1, treap.calcRange(0, 21));
  EXPECT_EQ(0, treap.calcRange(0, 9));
  EXPECT_EQ(0, treap.calcRange(9, 10));
  EXPECT_EQ(0, treap.calcRange(10, 19));
  EXPECT_EQ(0, treap.calcRange(19, 20));
  EXPECT_EQ(1, treap.calcRange(20, 21));
}

TEST(TreapSetTest, initItems) {
  TreapSet<int> treap;
  treap.initItems({{5, nullptr}, {10, nullptr}, {11, nullptr}});
  EXPECT_EQ(0, treap.calcPrefix(5));
  EXPECT_EQ(1, treap.calcPrefix(6));
  EXPECT_EQ(1, treap.calcPrefix(7));
  EXPECT_EQ(1, treap.calcPrefix(10));
  EXPECT_EQ(2, treap.calcPrefix(11));
  EXPECT_EQ(3, treap.calcPrefix(12));
  EXPECT_EQ(3, treap.calcPrefix(13));
}

} // namespace ds
