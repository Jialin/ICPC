#include "gtest/gtest.h"

#include "math/montgomery_mul.h"

namespace math {

TEST(MontgomeryMul, testSmall) {
  MontgomeryMul mont(13255);
  __uint128_t result;

  result = mont.convert(11234);
  EXPECT_EQ(result, 12824);
  result = mont.convert(124);
  EXPECT_EQ(result, 5234);

  result = mont.revert(mont.mul(mont.convert(11234), mont.convert(124)));
  EXPECT_EQ(result, 1241);
}

TEST(MontgomeryMul, testLarge) {
  __uint128_t mod = 2512449125679551613ULL;
  mod *= 12471213311231241ULL;
  __uint128_t x = 18446744012309551614ULL;
  x *= 12471241123ULL;
  __uint128_t y = 174435273709551614ULL;
  y *= 1248614133431432ULL;
  MontgomeryMul mont(mod);

  __uint128_t expect = 268398831344357297ULL;
  expect = expect * 100000000000000000ULL + 695512833362263ULL;
  __uint128_t result = mont.revert(mont.mul(mont.convert(x), mont.convert(y)));

  EXPECT_EQ(result, expect);
}

} // namespace math
