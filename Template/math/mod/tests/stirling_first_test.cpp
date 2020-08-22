#include "gtest/gtest.h"

#include "math/mod/stirling_first.h"

namespace math {

TEST(StirlingFirstTest, getUnsigned) {
  StirlingFirst stirling(6, 1000);
  EXPECT_EQ(stirling.getUnsigned(0, 0), 1);
  EXPECT_EQ(stirling.getUnsigned(0, 1), 0);
  EXPECT_EQ(stirling.getUnsigned(1, 0), 0);
  EXPECT_EQ(stirling.getUnsigned(1, 1), 1);
  EXPECT_EQ(stirling.getUnsigned(1, 2), 0);
  EXPECT_EQ(stirling.getUnsigned(2, 0), 0);
  EXPECT_EQ(stirling.getUnsigned(2, 1), 1);
  EXPECT_EQ(stirling.getUnsigned(2, 2), 1);
  EXPECT_EQ(stirling.getUnsigned(2, 3), 0);
  EXPECT_EQ(stirling.getUnsigned(3, 0), 0);
  EXPECT_EQ(stirling.getUnsigned(3, 1), 2);
  EXPECT_EQ(stirling.getUnsigned(3, 2), 3);
  EXPECT_EQ(stirling.getUnsigned(3, 3), 1);
  EXPECT_EQ(stirling.getUnsigned(3, 4), 0);
  EXPECT_EQ(stirling.getUnsigned(4, 0), 0);
  EXPECT_EQ(stirling.getUnsigned(4, 1), 6);
  EXPECT_EQ(stirling.getUnsigned(4, 2), 11);
  EXPECT_EQ(stirling.getUnsigned(4, 3), 6);
  EXPECT_EQ(stirling.getUnsigned(4, 4), 1);
  EXPECT_EQ(stirling.getUnsigned(4, 5), 0);
  EXPECT_EQ(stirling.getUnsigned(5, 0), 0);
  EXPECT_EQ(stirling.getUnsigned(5, 1), 24);
  EXPECT_EQ(stirling.getUnsigned(5, 2), 50);
  EXPECT_EQ(stirling.getUnsigned(5, 3), 35);
  EXPECT_EQ(stirling.getUnsigned(5, 4), 10);
  EXPECT_EQ(stirling.getUnsigned(5, 5), 1);
  EXPECT_EQ(stirling.getUnsigned(5, 6), 0);
}

TEST(StirlingFirstTest, getSigned) {
  StirlingFirst stirling(7, 1000);
  EXPECT_EQ(stirling.getSigned(6, 0), 0);
  EXPECT_EQ(stirling.getSigned(6, 1), 880);
  EXPECT_EQ(stirling.getSigned(6, 2), 274);
  EXPECT_EQ(stirling.getSigned(6, 3), 775);
  EXPECT_EQ(stirling.getSigned(6, 4), 85);
  EXPECT_EQ(stirling.getSigned(6, 5), 985);
  EXPECT_EQ(stirling.getSigned(6, 6), 1);
  EXPECT_EQ(stirling.getSigned(6, 7), 0);
}

} // namespace math
