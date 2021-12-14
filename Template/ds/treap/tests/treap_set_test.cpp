#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#define TREAP_SET_ALL
#include "ds/treap/base_treap_macros.h"
#include "ds/treap/treap_set_macros.h"

#include "ds/treap/treap_set.h"

namespace ds {

TEST(TreapSetTest, countPrefix) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(0, treap.countPrefix(11));
  EXPECT_EQ(0, treap.countPrefix(20));
  EXPECT_EQ(0, treap.countPrefix(21));

  treap.insert(10);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(1, treap.countPrefix(11));
  EXPECT_EQ(1, treap.countPrefix(20));
  EXPECT_EQ(1, treap.countPrefix(21));

  treap.insert(20);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(1, treap.countPrefix(11));
  EXPECT_EQ(1, treap.countPrefix(20));
  EXPECT_EQ(2, treap.countPrefix(21));

  treap.erase(15);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(1, treap.countPrefix(11));
  EXPECT_EQ(1, treap.countPrefix(20));
  EXPECT_EQ(2, treap.countPrefix(21));

  treap.erase(10);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(0, treap.countPrefix(11));
  EXPECT_EQ(0, treap.countPrefix(20));
  EXPECT_EQ(1, treap.countPrefix(21));

  treap.insert(5);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(1, treap.countPrefix(10));
  EXPECT_EQ(1, treap.countPrefix(11));
  EXPECT_EQ(1, treap.countPrefix(20));
  EXPECT_EQ(2, treap.countPrefix(21));

  treap.insert(-5);
  EXPECT_EQ(1, treap.countPrefix(1));
  EXPECT_EQ(2, treap.countPrefix(10));
  EXPECT_EQ(2, treap.countPrefix(11));
  EXPECT_EQ(2, treap.countPrefix(20));
  EXPECT_EQ(3, treap.countPrefix(21));

  treap.erase(10);
  EXPECT_EQ(1, treap.countPrefix(1));
  EXPECT_EQ(2, treap.countPrefix(10));
  EXPECT_EQ(2, treap.countPrefix(11));
  EXPECT_EQ(2, treap.countPrefix(20));
  EXPECT_EQ(3, treap.countPrefix(21));

  treap.erase(-5);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(1, treap.countPrefix(10));
  EXPECT_EQ(1, treap.countPrefix(11));
  EXPECT_EQ(1, treap.countPrefix(20));
  EXPECT_EQ(2, treap.countPrefix(21));

  treap.erase(5);
  EXPECT_EQ(0, treap.countPrefix(1));
  EXPECT_EQ(0, treap.countPrefix(10));
  EXPECT_EQ(0, treap.countPrefix(11));
  EXPECT_EQ(0, treap.countPrefix(20));
  EXPECT_EQ(1, treap.countPrefix(21));
}

TEST(TreapSetTest, countSuffix) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.countSuffix(0));
  EXPECT_EQ(0, treap.countSuffix(9));
  EXPECT_EQ(0, treap.countSuffix(10));
  EXPECT_EQ(0, treap.countSuffix(19));
  EXPECT_EQ(0, treap.countSuffix(20));

  treap.insert(10);
  EXPECT_EQ(1, treap.countSuffix(0));
  EXPECT_EQ(1, treap.countSuffix(9));
  EXPECT_EQ(1, treap.countSuffix(10));
  EXPECT_EQ(0, treap.countSuffix(19));
  EXPECT_EQ(0, treap.countSuffix(20));

  treap.insert(20);
  EXPECT_EQ(2, treap.countSuffix(0));
  EXPECT_EQ(2, treap.countSuffix(9));
  EXPECT_EQ(2, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.insert(5);
  EXPECT_EQ(3, treap.countSuffix(0));
  EXPECT_EQ(2, treap.countSuffix(9));
  EXPECT_EQ(2, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.insert(-5);
  EXPECT_EQ(3, treap.countSuffix(0));
  EXPECT_EQ(2, treap.countSuffix(9));
  EXPECT_EQ(2, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.erase(10);
  EXPECT_EQ(2, treap.countSuffix(0));
  EXPECT_EQ(1, treap.countSuffix(9));
  EXPECT_EQ(1, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.erase(10);
  EXPECT_EQ(2, treap.countSuffix(0));
  EXPECT_EQ(1, treap.countSuffix(9));
  EXPECT_EQ(1, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.erase(-5);
  EXPECT_EQ(2, treap.countSuffix(0));
  EXPECT_EQ(1, treap.countSuffix(9));
  EXPECT_EQ(1, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));

  treap.erase(5);
  EXPECT_EQ(1, treap.countSuffix(0));
  EXPECT_EQ(1, treap.countSuffix(9));
  EXPECT_EQ(1, treap.countSuffix(10));
  EXPECT_EQ(1, treap.countSuffix(19));
  EXPECT_EQ(1, treap.countSuffix(20));
}

TEST(TreapSetTest, countRange) {
  TreapSet<int> treap;
  EXPECT_EQ(0, treap.countRange(0, 21));
  EXPECT_EQ(0, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(0, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(0, treap.countRange(20, 21));

  treap.insert(10);
  EXPECT_EQ(1, treap.countRange(0, 21));
  EXPECT_EQ(0, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(1, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(0, treap.countRange(20, 21));

  treap.insert(20);
  EXPECT_EQ(2, treap.countRange(0, 21));
  EXPECT_EQ(0, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(1, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.insert(5);
  EXPECT_EQ(3, treap.countRange(0, 21));
  EXPECT_EQ(1, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(1, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.insert(-5);
  EXPECT_EQ(3, treap.countRange(0, 21));
  EXPECT_EQ(1, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(1, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.erase(10);
  EXPECT_EQ(2, treap.countRange(0, 21));
  EXPECT_EQ(1, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(0, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.erase(10);
  EXPECT_EQ(2, treap.countRange(0, 21));
  EXPECT_EQ(1, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(0, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.erase(-5);
  EXPECT_EQ(2, treap.countRange(0, 21));
  EXPECT_EQ(1, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(0, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));

  treap.erase(5);
  EXPECT_EQ(1, treap.countRange(0, 21));
  EXPECT_EQ(0, treap.countRange(0, 9));
  EXPECT_EQ(0, treap.countRange(9, 10));
  EXPECT_EQ(0, treap.countRange(10, 19));
  EXPECT_EQ(0, treap.countRange(19, 20));
  EXPECT_EQ(1, treap.countRange(20, 21));
}

TEST(TreapSetTest, initOrderedItems) {
  TreapSet<int> treap;
  treap.initOrderedItems({{5, nullptr}, {10, nullptr}, {11, nullptr}});
  EXPECT_EQ(0, treap.countPrefix(5));
  EXPECT_EQ(1, treap.countPrefix(6));
  EXPECT_EQ(1, treap.countPrefix(7));
  EXPECT_EQ(1, treap.countPrefix(10));
  EXPECT_EQ(2, treap.countPrefix(11));
  EXPECT_EQ(3, treap.countPrefix(12));
  EXPECT_EQ(3, treap.countPrefix(13));
}

} // namespace ds
