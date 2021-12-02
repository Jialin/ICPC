#include "gtest/gtest.h"

#define BASE_LAZY_TREAP_ALL
#include "ds/treap/base_lazy_treap_macros.h"

#include "ds/treap/lazy_treap_reverse.h"

namespace ds {

TEST(LazyTreapReverseTest, updateRangeByKth) {
  ds::LazyTreapReverse treap;
  treap.initOrderedValues(vector<nullptr_t>(5));

  treap.updateRangeByKth(0, 3, true);
  treap.updateRangeByKth(3, 5, true);
  EXPECT_EQ(2, treap.calcKth(0)->_key);
  EXPECT_EQ(1, treap.calcKth(1)->_key);
  EXPECT_EQ(0, treap.calcKth(2)->_key);
  EXPECT_EQ(4, treap.calcKth(3)->_key);
  EXPECT_EQ(3, treap.calcKth(4)->_key);

  treap.updateRangeByKth(0, 4, true);
  treap.updateRangeByKth(1, 5, true);
  EXPECT_EQ(4, treap.calcKth(0)->_key);
  EXPECT_EQ(3, treap.calcKth(1)->_key);
  EXPECT_EQ(2, treap.calcKth(2)->_key);
  EXPECT_EQ(1, treap.calcKth(3)->_key);
  EXPECT_EQ(0, treap.calcKth(4)->_key);
}

TEST(LazyTreapReverseTest, cyclicRotateRightByKth) {
  ds::LazyTreapReverse treap;
  treap.initOrderedValues(vector<nullptr_t>(5));

  treap.cyclicRotateRightByKth(0, 3);
  treap.cyclicRotateRightByKth(3, 5);
  EXPECT_EQ(2, treap.calcKth(0)->_key);
  EXPECT_EQ(0, treap.calcKth(1)->_key);
  EXPECT_EQ(1, treap.calcKth(2)->_key);
  EXPECT_EQ(4, treap.calcKth(3)->_key);
  EXPECT_EQ(3, treap.calcKth(4)->_key);

  treap.cyclicRotateRightByKth(0, 4);
  treap.cyclicRotateRightByKth(1, 5);
  EXPECT_EQ(4, treap.calcKth(0)->_key);
  EXPECT_EQ(3, treap.calcKth(1)->_key);
  EXPECT_EQ(2, treap.calcKth(2)->_key);
  EXPECT_EQ(0, treap.calcKth(3)->_key);
  EXPECT_EQ(1, treap.calcKth(4)->_key);
}

} // namespace ds
