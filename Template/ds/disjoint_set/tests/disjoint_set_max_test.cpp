#include "gtest/gtest.h"

#define BASE_DISJOINT_SET_VALUE_ALL
#include "ds/disjoint_set/base_disjoint_set_value_macros.h"

#include "ds/disjoint_set/disjoint_set_max.h"

using namespace std;

namespace ds {

TEST(DisjointSetMaxTest, basic) {
  ds::DisjointSetMax<int> dset;
  dset.init({10, 20, 30, 40, 50});

  EXPECT_EQ(10, dset.calcSetValue(0));
  EXPECT_EQ(20, dset.calcSetValue(1));
  EXPECT_EQ(30, dset.calcSetValue(2));
  EXPECT_EQ(40, dset.calcSetValue(3));
  EXPECT_EQ(50, dset.calcSetValue(4));

  EXPECT_TRUE(dset.unionSet(2, 4));
  EXPECT_EQ(10, dset.calcSetValue(0));
  EXPECT_EQ(20, dset.calcSetValue(1));
  EXPECT_EQ(50, dset.calcSetValue(2));
  EXPECT_EQ(40, dset.calcSetValue(3));
  EXPECT_EQ(50, dset.calcSetValue(4));

  EXPECT_TRUE(dset.unionSet(3, 1));
  EXPECT_EQ(10, dset.calcSetValue(0));
  EXPECT_EQ(40, dset.calcSetValue(1));
  EXPECT_EQ(50, dset.calcSetValue(2));
  EXPECT_EQ(40, dset.calcSetValue(3));
  EXPECT_EQ(50, dset.calcSetValue(4));

  EXPECT_TRUE(dset.unionSet(0, 4));
  EXPECT_EQ(50, dset.calcSetValue(0));
  EXPECT_EQ(40, dset.calcSetValue(1));
  EXPECT_EQ(50, dset.calcSetValue(2));
  EXPECT_EQ(40, dset.calcSetValue(3));
  EXPECT_EQ(50, dset.calcSetValue(4));

  EXPECT_TRUE(dset.unionSet(0, 1));
  EXPECT_EQ(50, dset.calcSetValue(0));
  EXPECT_EQ(50, dset.calcSetValue(1));
  EXPECT_EQ(50, dset.calcSetValue(2));
  EXPECT_EQ(50, dset.calcSetValue(3));
  EXPECT_EQ(50, dset.calcSetValue(4));
}

} // namespace ds
