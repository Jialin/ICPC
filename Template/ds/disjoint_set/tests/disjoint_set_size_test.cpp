#include "gtest/gtest.h"

#define DISJOINT_SET_SIZE_ALL
#include "ds/disjoint_set/disjoint_set_size_macros.h"

#include "ds/disjoint_set/disjoint_set_size.h"

using namespace std;

namespace ds {

TEST(DisjointSetSizeTest, basic) {
  ds::DisjointSetSize dset;
  dset.init(5);

  EXPECT_TRUE(dset.unionSet(1, 2));
  EXPECT_EQ(0, dset.findSet(0));
  EXPECT_EQ(1, dset.findSet(1));
  EXPECT_EQ(1, dset.findSet(2));
  EXPECT_EQ(3, dset.findSet(3));
  EXPECT_EQ(4, dset.findSet(4));

  EXPECT_TRUE(dset.unionSet(2, 3));
  EXPECT_EQ(0, dset.findSet(0));
  EXPECT_EQ(1, dset.findSet(1));
  EXPECT_EQ(1, dset.findSet(2));
  EXPECT_EQ(1, dset.findSet(3));
  EXPECT_EQ(4, dset.findSet(4));

  EXPECT_FALSE(dset.unionSet(1, 3));
  EXPECT_EQ(0, dset.findSet(0));
  EXPECT_EQ(1, dset.findSet(1));
  EXPECT_EQ(1, dset.findSet(2));
  EXPECT_EQ(1, dset.findSet(3));
  EXPECT_EQ(4, dset.findSet(4));

  EXPECT_TRUE(dset.unionSet(0, 4));
  EXPECT_EQ(0, dset.findSet(0));
  EXPECT_EQ(1, dset.findSet(1));
  EXPECT_EQ(1, dset.findSet(2));
  EXPECT_EQ(1, dset.findSet(3));
  EXPECT_EQ(0, dset.findSet(4));

  EXPECT_TRUE(dset.unionSet(0, 3));
  EXPECT_EQ(1, dset.findSet(0));
  EXPECT_EQ(1, dset.findSet(1));
  EXPECT_EQ(1, dset.findSet(2));
  EXPECT_EQ(1, dset.findSet(3));
  EXPECT_EQ(1, dset.findSet(4));

  EXPECT_FALSE(dset.unionSet(0, 0));
  EXPECT_FALSE(dset.unionSet(0, 1));
  EXPECT_FALSE(dset.unionSet(0, 2));
  EXPECT_FALSE(dset.unionSet(0, 3));
  EXPECT_FALSE(dset.unionSet(0, 4));
  EXPECT_FALSE(dset.unionSet(1, 0));
  EXPECT_FALSE(dset.unionSet(1, 1));
  EXPECT_FALSE(dset.unionSet(1, 2));
  EXPECT_FALSE(dset.unionSet(1, 3));
  EXPECT_FALSE(dset.unionSet(1, 4));
  EXPECT_FALSE(dset.unionSet(2, 0));
  EXPECT_FALSE(dset.unionSet(2, 1));
  EXPECT_FALSE(dset.unionSet(2, 2));
  EXPECT_FALSE(dset.unionSet(2, 3));
  EXPECT_FALSE(dset.unionSet(2, 4));
  EXPECT_FALSE(dset.unionSet(3, 0));
  EXPECT_FALSE(dset.unionSet(3, 1));
  EXPECT_FALSE(dset.unionSet(3, 2));
  EXPECT_FALSE(dset.unionSet(3, 3));
  EXPECT_FALSE(dset.unionSet(3, 4));
  EXPECT_FALSE(dset.unionSet(4, 0));
  EXPECT_FALSE(dset.unionSet(4, 1));
  EXPECT_FALSE(dset.unionSet(4, 2));
  EXPECT_FALSE(dset.unionSet(4, 3));
  EXPECT_FALSE(dset.unionSet(4, 4));
}

} // namespace ds
