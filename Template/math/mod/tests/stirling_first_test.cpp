#include "gtest/gtest.h"

#include "math/mod/stirling_first.h"

namespace math {

TEST(StirlingFirstTest, calcUnsigned) {
  StirlingFirst stirling(6, 1000);
  EXPECT_EQ(stirling.calcUnsigned(0, 0), 1);
  EXPECT_EQ(stirling.calcUnsigned(0, 1), 0);
  EXPECT_EQ(stirling.calcUnsigned(1, 0), 0);
  EXPECT_EQ(stirling.calcUnsigned(1, 1), 1);
  EXPECT_EQ(stirling.calcUnsigned(1, 2), 0);
  EXPECT_EQ(stirling.calcUnsigned(2, 0), 0);
  EXPECT_EQ(stirling.calcUnsigned(2, 1), 1);
  EXPECT_EQ(stirling.calcUnsigned(2, 2), 1);
  EXPECT_EQ(stirling.calcUnsigned(2, 3), 0);
  EXPECT_EQ(stirling.calcUnsigned(3, 0), 0);
  EXPECT_EQ(stirling.calcUnsigned(3, 1), 2);
  EXPECT_EQ(stirling.calcUnsigned(3, 2), 3);
  EXPECT_EQ(stirling.calcUnsigned(3, 3), 1);
  EXPECT_EQ(stirling.calcUnsigned(3, 4), 0);
  EXPECT_EQ(stirling.calcUnsigned(4, 0), 0);
  EXPECT_EQ(stirling.calcUnsigned(4, 1), 6);
  EXPECT_EQ(stirling.calcUnsigned(4, 2), 11);
  EXPECT_EQ(stirling.calcUnsigned(4, 3), 6);
  EXPECT_EQ(stirling.calcUnsigned(4, 4), 1);
  EXPECT_EQ(stirling.calcUnsigned(4, 5), 0);
  EXPECT_EQ(stirling.calcUnsigned(5, 0), 0);
  EXPECT_EQ(stirling.calcUnsigned(5, 1), 24);
  EXPECT_EQ(stirling.calcUnsigned(5, 2), 50);
  EXPECT_EQ(stirling.calcUnsigned(5, 3), 35);
  EXPECT_EQ(stirling.calcUnsigned(5, 4), 10);
  EXPECT_EQ(stirling.calcUnsigned(5, 5), 1);
  EXPECT_EQ(stirling.calcUnsigned(5, 6), 0);
}

TEST(StirlingFirstTest, calcSigned) {
  StirlingFirst stirling(7, 1000);
  EXPECT_EQ(stirling.calcSigned(6, 0), 0);
  EXPECT_EQ(stirling.calcSigned(6, 1), 880);
  EXPECT_EQ(stirling.calcSigned(6, 2), 274);
  EXPECT_EQ(stirling.calcSigned(6, 3), 775);
  EXPECT_EQ(stirling.calcSigned(6, 4), 85);
  EXPECT_EQ(stirling.calcSigned(6, 5), 985);
  EXPECT_EQ(stirling.calcSigned(6, 6), 1);
  EXPECT_EQ(stirling.calcSigned(6, 7), 0);
}

} // namespace math
