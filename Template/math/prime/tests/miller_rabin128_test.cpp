#include "gtest/gtest.h"

#include "math/prime/miller_rabin128.h"

namespace math {

TEST(MillerRabin128, testPrime) {
  MontgomeryMul mont;
  EXPECT_TRUE(millerRabin128(2, mont));

  mont.init(3);
  EXPECT_TRUE(millerRabin128(3, mont, false));

  EXPECT_FALSE(millerRabin128(1000000007, mont, false));
  mont.init(1000000007);
  EXPECT_TRUE(millerRabin128(1000000007, mont, false));
}

TEST(MillerRabin128, testComposite) {
  MontgomeryMul mont;

  EXPECT_FALSE(millerRabin128(0, mont));
  EXPECT_FALSE(millerRabin128(1, mont));
  EXPECT_FALSE(millerRabin128(4, mont));
  EXPECT_FALSE(millerRabin128(561, mont));
  EXPECT_FALSE(millerRabin128(3215031751, mont));
}

TEST(MillerRabin128, testCarmichael) {
  MontgomeryMul mont;

  EXPECT_FALSE(millerRabin128(6601, mont));
  EXPECT_FALSE(millerRabin128(62745, mont));
  EXPECT_FALSE(millerRabin128(63973, mont));
  EXPECT_FALSE(millerRabin128(75361, mont));
}

TEST(MillerRabin128, testLarge) {
  MontgomeryMul mont;
  EXPECT_TRUE(millerRabin128(1000000000000037ULL, mont));
  EXPECT_FALSE(millerRabin128(1000000000000039ULL, mont));

  EXPECT_TRUE(millerRabin128(
      __uint128_t(100000000000000000ULL) * 1000000000 + 67, mont));
  EXPECT_FALSE(millerRabin128(
      __uint128_t(100000000000000000ULL) * 1000000000 + 69, mont));
}

} // namespace math
