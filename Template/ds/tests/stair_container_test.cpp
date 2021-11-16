#include "gtest/gtest.h"

#define STAIR_CONTAINER_ALL
#include "ds/stair_container_macros.h"

#include "ds/stair_container.h"

namespace ds {

TEST(StairContainerTest, basic) {
  StairContainer<int> stairs;

  EXPECT_FALSE(stairs.isFullyInside(3, 1));
  EXPECT_FALSE(stairs.isFullyInside(7, 8));
  EXPECT_FALSE(stairs.isFullyInside(7, 12));
  EXPECT_FALSE(stairs.isFullyInside(12, 3));

  stairs.update(5, 15);
  EXPECT_TRUE(stairs.isFullyInside(3, 1));
  EXPECT_FALSE(stairs.isFullyInside(7, 8));
  EXPECT_FALSE(stairs.isFullyInside(7, 12));
  EXPECT_FALSE(stairs.isFullyInside(12, 3));

  stairs.update(10, 10);
  EXPECT_TRUE(stairs.isFullyInside(3, 1));
  EXPECT_TRUE(stairs.isFullyInside(7, 8));
  EXPECT_FALSE(stairs.isFullyInside(7, 12));
  EXPECT_FALSE(stairs.isFullyInside(12, 3));

  stairs.update(15, 5);
  EXPECT_TRUE(stairs.isFullyInside(3, 1));
  EXPECT_TRUE(stairs.isFullyInside(7, 8));
  EXPECT_FALSE(stairs.isFullyInside(7, 12));
  EXPECT_TRUE(stairs.isFullyInside(12, 3));

  stairs.update(20, 20);
  EXPECT_TRUE(stairs.isFullyInside(3, 1));
  EXPECT_TRUE(stairs.isFullyInside(7, 8));
  EXPECT_TRUE(stairs.isFullyInside(7, 12));
  EXPECT_TRUE(stairs.isFullyInside(12, 3));
  EXPECT_EQ(1, stairs._vs.size());
  EXPECT_EQ(20, stairs._vs[20]);
}

} // namespace ds
