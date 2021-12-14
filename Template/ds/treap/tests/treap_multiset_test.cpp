#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#define TREAP_MULTISET_ALL
#include "ds/treap/base_treap_macros.h"
#include "ds/treap/treap_multiset_macros.h"

#include "ds/treap/treap_multiset.h"

namespace ds {

TEST(TreapMultisetTest, calcKth) {
  TreapMultiset<int> treap;
  EXPECT_FALSE(treap.calcKthByRange(-1));
  EXPECT_FALSE(treap.calcKthByRange(0));

  treap.insert(10);
  ASSERT_TRUE(treap.calcKthByRange(0));
  EXPECT_EQ(10, treap.calcKthByRange(0)->_key);
  EXPECT_FALSE(treap.calcKthByRange(1));

  treap.insert(5);
  ASSERT_TRUE(treap.calcKthByRange(0));
  EXPECT_EQ(5, treap.calcKthByRange(0)->_key);
  ASSERT_TRUE(treap.calcKthByRange(1));
  EXPECT_EQ(10, treap.calcKthByRange(1)->_key);
  EXPECT_FALSE(treap.calcKthByRange(2));

  treap.insert(10);
  ASSERT_TRUE(treap.calcKthByRange(0));
  EXPECT_EQ(5, treap.calcKthByRange(0)->_key);
  ASSERT_TRUE(treap.calcKthByRange(1));
  EXPECT_EQ(10, treap.calcKthByRange(1)->_key);
  ASSERT_TRUE(treap.calcKthByRange(2));
  EXPECT_EQ(10, treap.calcKthByRange(2)->_key);
  EXPECT_FALSE(treap.calcKthByRange(3));

  treap.erase(5);
  ASSERT_TRUE(treap.calcKthByRange(0));
  EXPECT_EQ(10, treap.calcKthByRange(0)->_key);
  ASSERT_TRUE(treap.calcKthByRange(1));
  EXPECT_EQ(10, treap.calcKthByRange(1)->_key);
  EXPECT_FALSE(treap.calcKthByRange(2));

  treap.erase(10);
  EXPECT_FALSE(treap.calcKthByRange(-1));
  EXPECT_FALSE(treap.calcKthByRange(0));
}

} // namespace ds
