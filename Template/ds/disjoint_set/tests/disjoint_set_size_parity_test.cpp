#include "gtest/gtest.h"

#define DISJOINT_SET_SIZE_PARITY_ALL
#include "ds/disjoint_set/disjoint_set_size_parity_macros.h"

#include "ds/disjoint_set/disjoint_set_size_parity.h"

using namespace std;

namespace ds {

TEST(DisjointSetSizeParityTest, basic) {
  DisjointSetSizeParity dset;
  dset.init(5);
  bool valid;

  EXPECT_TRUE(dset.unionSet(0, 1, false, valid));
  EXPECT_TRUE(valid);
  EXPECT_TRUE(dset.unionSet(1, 2, true, valid));
  EXPECT_TRUE(valid);
  EXPECT_TRUE(dset.unionSet(2, 3, true, valid));
  EXPECT_TRUE(valid);
  EXPECT_TRUE(dset.unionSet(3, 4, true, valid));
  EXPECT_TRUE(valid);

  EXPECT_FALSE(dset.unionSet(0, 2, true, valid));
  EXPECT_TRUE(valid);
  EXPECT_FALSE(dset.unionSet(0, 2, false, valid));
  EXPECT_FALSE(valid);

  EXPECT_FALSE(dset.unionSet(0, 3, true, valid));
  EXPECT_FALSE(valid);
  EXPECT_FALSE(dset.unionSet(0, 3, false, valid));
  EXPECT_TRUE(valid);
}

TEST(DisjointSetSizeParityTest, selfCheck) {
  DisjointSetSizeParity dset;
  dset.init(2);
  bool valid;

  EXPECT_FALSE(dset.unionSet(0, 0, false, valid));
  EXPECT_TRUE(valid);
  EXPECT_FALSE(dset.unionSet(1, 1, true, valid));
  EXPECT_FALSE(valid);
}

} // namespace ds
