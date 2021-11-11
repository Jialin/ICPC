#include "gtest/gtest.h"

#define DISJOINT_SET_SIZE_GROUPS_ALL
#include "ds/disjoint_set/disjoint_set_size_groups_macros.h"

#include "ds/disjoint_set/disjoint_set_size_groups.h"

using namespace std;

namespace ds {

TEST(DisjointSetSizeGroupsTest, basic) {
  DisjointSetSizeGroups dset;
  dset.init(5, 3);
  bool valid;

  EXPECT_TRUE(dset.unionSet(0, 1, 1, valid));
  EXPECT_TRUE(valid);
  EXPECT_TRUE(dset.unionSet(1, 2, 1, valid));
  EXPECT_TRUE(valid);
  EXPECT_FALSE(dset.unionSet(0, 2, 2, valid));
  EXPECT_TRUE(valid);
  EXPECT_FALSE(dset.unionSet(0, 2, 1, valid));
  EXPECT_FALSE(valid);
}

TEST(DisjointSetSizeGroupsTest, selfCheck) {
  DisjointSetSizeGroups dset;
  dset.init(3, 3);
  bool valid;

  EXPECT_FALSE(dset.unionSet(0, 0, 0, valid));
  EXPECT_TRUE(valid);
  EXPECT_FALSE(dset.unionSet(0, 0, 1, valid));
  EXPECT_FALSE(valid);
  EXPECT_FALSE(dset.unionSet(0, 0, 2, valid));
  EXPECT_FALSE(valid);
}

} // namespace ds
