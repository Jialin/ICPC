#include "gtest/gtest.h"

#define BASE_DISJOINT_SET_VALUE_ALL
#include "ds/disjoint_set/base_disjoint_set_value_macros.h"

#include "ds/disjoint_set/disjoint_set_min_max.h"

using namespace std;

namespace ds {

TEST(DisjointSetMaxTest, basic) {
  ds::DisjointSetMinMax<int> dset;
  dset.init({{10, 10}, {20, 20}, {30, 30}, {40, 40}, {50, 50}});
  pair<int, int> res;

  res = dset.calcSetValue(0);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(10, res.second);
  res = dset.calcSetValue(1);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(20, res.second);
  res = dset.calcSetValue(2);
  EXPECT_EQ(30, res.first);
  EXPECT_EQ(30, res.second);
  res = dset.calcSetValue(3);
  EXPECT_EQ(40, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(4);
  EXPECT_EQ(50, res.first);
  EXPECT_EQ(50, res.second);

  EXPECT_TRUE(dset.unionSet(2, 4));
  res = dset.calcSetValue(0);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(10, res.second);
  res = dset.calcSetValue(1);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(20, res.second);
  res = dset.calcSetValue(2);
  EXPECT_EQ(30, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(3);
  EXPECT_EQ(40, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(4);
  EXPECT_EQ(30, res.first);
  EXPECT_EQ(50, res.second);

  EXPECT_TRUE(dset.unionSet(3, 1));
  res = dset.calcSetValue(0);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(10, res.second);
  res = dset.calcSetValue(1);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(2);
  EXPECT_EQ(30, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(3);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(4);
  EXPECT_EQ(30, res.first);
  EXPECT_EQ(50, res.second);

  EXPECT_TRUE(dset.unionSet(0, 4));
  res = dset.calcSetValue(0);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(1);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(2);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(3);
  EXPECT_EQ(20, res.first);
  EXPECT_EQ(40, res.second);
  res = dset.calcSetValue(4);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);

  EXPECT_TRUE(dset.unionSet(0, 1));
  res = dset.calcSetValue(0);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(1);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(2);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(3);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
  res = dset.calcSetValue(4);
  EXPECT_EQ(10, res.first);
  EXPECT_EQ(50, res.second);
}

} // namespace ds
