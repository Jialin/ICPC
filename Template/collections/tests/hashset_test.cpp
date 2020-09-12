#include "gtest/gtest.h"

#include "collections/hashset.h"

namespace collections {

TEST(HashsetTest, basic) {
  Hashset<int> hset(7);
  EXPECT_EQ(hset._vs._edgeIdx, 0);

  hset.add(1);
  hset.add(2);
  hset.add(3);
  EXPECT_EQ(hset._vs._edgeIdx, 3);
  EXPECT_FALSE(hset.contains(0));
  EXPECT_TRUE(hset.contains(1));
  EXPECT_TRUE(hset.contains(2));
  EXPECT_TRUE(hset.contains(3));
  EXPECT_FALSE(hset.contains(4));
  EXPECT_FALSE(hset.contains(7));

  hset.add(1);
  hset.add(2);
  hset.add(3);
  EXPECT_EQ(hset._vs._edgeIdx, 3);

  hset.add(1, true /* forceAdd */);
  hset.add(2, true /* forceAdd */);
  hset.add(3, true /* forceAdd */);
  EXPECT_EQ(hset._vs._edgeIdx, 6);
  EXPECT_FALSE(hset.contains(0));
  EXPECT_TRUE(hset.contains(1));
  EXPECT_TRUE(hset.contains(2));
  EXPECT_TRUE(hset.contains(3));
  EXPECT_FALSE(hset.contains(4));
  EXPECT_FALSE(hset.contains(7));

  hset.add(0);
  hset.add(4);
  EXPECT_TRUE(hset.contains(0));
  EXPECT_TRUE(hset.contains(1));
  EXPECT_TRUE(hset.contains(2));
  EXPECT_TRUE(hset.contains(3));
  EXPECT_TRUE(hset.contains(4));
  EXPECT_FALSE(hset.contains(7));

  hset.add(7);
  EXPECT_TRUE(hset.contains(0));
  EXPECT_TRUE(hset.contains(1));
  EXPECT_TRUE(hset.contains(2));
  EXPECT_TRUE(hset.contains(3));
  EXPECT_TRUE(hset.contains(4));
  EXPECT_TRUE(hset.contains(7));
}

} // namespace collections
