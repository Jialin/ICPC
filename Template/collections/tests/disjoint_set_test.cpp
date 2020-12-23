#include "gtest/gtest.h"

#include "collections/disjoint_set.h"

namespace collections {

TEST(DisjointSet, test) {
  DisjointSet dset(4);
  EXPECT_TRUE(dset.isFriend(0, 0));
  EXPECT_FALSE(dset.isFriend(0, 1));
  EXPECT_FALSE(dset.isFriend(0, 2));
  EXPECT_FALSE(dset.isFriend(0, 3));
  EXPECT_FALSE(dset.isFriend(1, 0));
  EXPECT_TRUE(dset.isFriend(1, 1));
  EXPECT_FALSE(dset.isFriend(1, 2));
  EXPECT_FALSE(dset.isFriend(1, 3));
  EXPECT_FALSE(dset.isFriend(2, 0));
  EXPECT_FALSE(dset.isFriend(2, 1));
  EXPECT_TRUE(dset.isFriend(2, 2));
  EXPECT_FALSE(dset.isFriend(2, 3));
  EXPECT_FALSE(dset.isFriend(3, 0));
  EXPECT_FALSE(dset.isFriend(3, 1));
  EXPECT_FALSE(dset.isFriend(3, 2));
  EXPECT_TRUE(dset.isFriend(3, 3));

  dset.setFriend(0, 1);
  EXPECT_TRUE(dset.isFriend(0, 0));
  EXPECT_TRUE(dset.isFriend(0, 1));
  EXPECT_FALSE(dset.isFriend(0, 2));
  EXPECT_FALSE(dset.isFriend(0, 3));
  EXPECT_TRUE(dset.isFriend(1, 0));
  EXPECT_TRUE(dset.isFriend(1, 1));
  EXPECT_FALSE(dset.isFriend(1, 2));
  EXPECT_FALSE(dset.isFriend(1, 3));
  EXPECT_FALSE(dset.isFriend(2, 0));
  EXPECT_FALSE(dset.isFriend(2, 1));
  EXPECT_TRUE(dset.isFriend(2, 2));
  EXPECT_FALSE(dset.isFriend(2, 3));
  EXPECT_FALSE(dset.isFriend(3, 0));
  EXPECT_FALSE(dset.isFriend(3, 1));
  EXPECT_FALSE(dset.isFriend(3, 2));
  EXPECT_TRUE(dset.isFriend(3, 3));

  dset.setFriend(2, 3);
  EXPECT_TRUE(dset.isFriend(0, 0));
  EXPECT_TRUE(dset.isFriend(0, 1));
  EXPECT_FALSE(dset.isFriend(0, 2));
  EXPECT_FALSE(dset.isFriend(0, 3));
  EXPECT_TRUE(dset.isFriend(1, 0));
  EXPECT_TRUE(dset.isFriend(1, 1));
  EXPECT_FALSE(dset.isFriend(1, 2));
  EXPECT_FALSE(dset.isFriend(1, 3));
  EXPECT_FALSE(dset.isFriend(2, 0));
  EXPECT_FALSE(dset.isFriend(2, 1));
  EXPECT_TRUE(dset.isFriend(2, 2));
  EXPECT_TRUE(dset.isFriend(2, 3));
  EXPECT_FALSE(dset.isFriend(3, 0));
  EXPECT_FALSE(dset.isFriend(3, 1));
  EXPECT_TRUE(dset.isFriend(3, 2));
  EXPECT_TRUE(dset.isFriend(3, 3));

  dset.setFriend(0, 3);
  EXPECT_TRUE(dset.isFriend(0, 0));
  EXPECT_TRUE(dset.isFriend(0, 1));
  EXPECT_TRUE(dset.isFriend(0, 2));
  EXPECT_TRUE(dset.isFriend(0, 3));
  EXPECT_TRUE(dset.isFriend(1, 0));
  EXPECT_TRUE(dset.isFriend(1, 1));
  EXPECT_TRUE(dset.isFriend(1, 2));
  EXPECT_TRUE(dset.isFriend(1, 3));
  EXPECT_TRUE(dset.isFriend(2, 0));
  EXPECT_TRUE(dset.isFriend(2, 1));
  EXPECT_TRUE(dset.isFriend(2, 2));
  EXPECT_TRUE(dset.isFriend(2, 3));
  EXPECT_TRUE(dset.isFriend(3, 0));
  EXPECT_TRUE(dset.isFriend(3, 1));
  EXPECT_TRUE(dset.isFriend(3, 2));
  EXPECT_TRUE(dset.isFriend(3, 3));
}

} // namespace collections
