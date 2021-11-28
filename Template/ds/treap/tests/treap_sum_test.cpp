#include "gtest/gtest.h"

#define BASE_TREAP_ALL
#include "ds/treap/base_treap_macros.h"

#include "ds/treap/treap_sum.h"

namespace ds {

TEST(TreapSumTest, basic) {
  TreapSum<int> treap;
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(0, treap.calcPrefix(11));
  EXPECT_EQ(0, treap.calcPrefix(20));
  EXPECT_EQ(0, treap.calcPrefix(21));

  treap.update(10, 100);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(100, treap.calcPrefix(11));
  EXPECT_EQ(100, treap.calcPrefix(20));
  EXPECT_EQ(100, treap.calcPrefix(21));

  treap.update(20, 200);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(0, treap.calcPrefix(10));
  EXPECT_EQ(100, treap.calcPrefix(11));
  EXPECT_EQ(100, treap.calcPrefix(20));
  EXPECT_EQ(300, treap.calcPrefix(21));

  treap.update(5, 300);
  EXPECT_EQ(0, treap.calcPrefix(1));
  EXPECT_EQ(300, treap.calcPrefix(10));
  EXPECT_EQ(400, treap.calcPrefix(11));
  EXPECT_EQ(400, treap.calcPrefix(20));
  EXPECT_EQ(600, treap.calcPrefix(21));

  treap.update(-5, 400);
  EXPECT_EQ(400, treap.calcPrefix(1));
  EXPECT_EQ(700, treap.calcPrefix(10));
  EXPECT_EQ(800, treap.calcPrefix(11));
  EXPECT_EQ(800, treap.calcPrefix(20));
  EXPECT_EQ(1000, treap.calcPrefix(21));
}

TEST(TreapSumTest, lowerBound) {
  TreapSum<int> treap;
  treap.update(5, 100);
  treap.update(10, 200);
  treap.update(15, 400);

  EXPECT_FALSE(treap.lowerBoundBounded(0, 701));
  const auto* res1 = treap.lowerBoundBounded(0, 700);
  ASSERT_TRUE(res1);
  EXPECT_EQ(15, res1->_key);
  const auto* res2 = treap.lowerBoundBounded(0, 699);
  ASSERT_TRUE(res2);
  EXPECT_EQ(15, res2->_key);
  const auto* res3 = treap.lowerBoundBounded(0, 301);
  ASSERT_TRUE(res3);
  EXPECT_EQ(15, res3->_key);
  const auto* res4 = treap.lowerBoundBounded(0, 300);
  ASSERT_TRUE(res4);
  EXPECT_EQ(10, res4->_key);
  const auto* res5 = treap.lowerBoundBounded(0, 299);
  ASSERT_TRUE(res5);
  EXPECT_EQ(10, res5->_key);
  const auto* res6 = treap.lowerBoundBounded(0, 101);
  ASSERT_TRUE(res6);
  EXPECT_EQ(10, res6->_key);
  const auto* res7 = treap.lowerBoundBounded(0, 100);
  ASSERT_TRUE(res7);
  EXPECT_EQ(5, res7->_key);
  const auto* res8 = treap.lowerBoundBounded(0, 99);
  ASSERT_TRUE(res8);
  EXPECT_EQ(5, res8->_key);

  const auto* res10 = treap.lowerBoundBounded(10, 199);
  ASSERT_TRUE(res10);
  EXPECT_EQ(10, res10->_key);
  const auto* res11 = treap.lowerBoundBounded(10, 200);
  ASSERT_TRUE(res11);
  EXPECT_EQ(10, res11->_key);
  const auto* res12 = treap.lowerBoundBounded(10, 201);
  ASSERT_TRUE(res12);
  EXPECT_EQ(15, res12->_key);
  const auto* res13 = treap.lowerBoundBounded(10, 599);
  ASSERT_TRUE(res13);
  EXPECT_EQ(15, res13->_key);
  const auto* res14 = treap.lowerBoundBounded(10, 600);
  ASSERT_TRUE(res14);
  EXPECT_EQ(15, res14->_key);
  EXPECT_FALSE(treap.lowerBoundBounded(10, 601));
}

} // namespace ds
