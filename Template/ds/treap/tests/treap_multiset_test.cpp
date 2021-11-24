#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_multiset.h"

namespace ds {

TEST(TreapMultisetTest, calcKth) {
  TreapMultiset<int> treap;
  EXPECT_FALSE(treap.calcKth(-1));
  EXPECT_FALSE(treap.calcKth(0));

  treap.insert(10);
  ASSERT_TRUE(treap.calcKth(0));
  EXPECT_EQ(10, treap.calcKth(0)->_key);
  EXPECT_FALSE(treap.calcKth(1));

  treap.insert(5);
  ASSERT_TRUE(treap.calcKth(0));
  EXPECT_EQ(5, treap.calcKth(0)->_key);
  ASSERT_TRUE(treap.calcKth(1));
  EXPECT_EQ(10, treap.calcKth(1)->_key);
  EXPECT_FALSE(treap.calcKth(2));

  treap.insert(10);
  ASSERT_TRUE(treap.calcKth(0));
  EXPECT_EQ(5, treap.calcKth(0)->_key);
  ASSERT_TRUE(treap.calcKth(1));
  EXPECT_EQ(10, treap.calcKth(1)->_key);
  ASSERT_TRUE(treap.calcKth(2));
  EXPECT_EQ(10, treap.calcKth(2)->_key);
  EXPECT_FALSE(treap.calcKth(3));

  treap.erase(5);
  ASSERT_TRUE(treap.calcKth(0));
  EXPECT_EQ(10, treap.calcKth(0)->_key);
  ASSERT_TRUE(treap.calcKth(1));
  EXPECT_EQ(10, treap.calcKth(1)->_key);
  EXPECT_FALSE(treap.calcKth(2));

  treap.erase(10);
  EXPECT_FALSE(treap.calcKth(-1));
  EXPECT_FALSE(treap.calcKth(0));
}

} // namespace ds
