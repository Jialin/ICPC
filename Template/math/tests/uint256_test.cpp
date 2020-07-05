#include "gtest/gtest.h"

#include "math/uint256.h"

namespace math {

TEST(UInt256, testSmall) {
  uint256 v = uint256::mul(11, 12);
  EXPECT_EQ(v.high, 0);
  EXPECT_EQ(v.low, 132);

  __uint128_t high = uint256::mulHigh(11, 12);
  EXPECT_EQ(high, 0);
}

TEST(UInt256, testLarge) {
  __uint128_t x = 18446744073709551614ULL;
  x *= 12371241123ULL;
  __uint128_t y = 1744073709551614ULL;
  y *= 1249614133431432ULL;
  uint256 v = uint256::mul(x, y);
  __uint128_t high = uint256::mulHigh(x, y);

  __uint128_t expect = 1461619448618933ULL;
  expect = expect * 1000000ULL + 743480ULL;
  EXPECT_EQ(v.high, expect);
  EXPECT_EQ(high, expect);
  expect = 14032365974406058644ULL;
  expect = expect * 10000000000000000000ULL + 4616145569432660576ULL;
  EXPECT_EQ(v.low, expect);
}

} // namespace math
