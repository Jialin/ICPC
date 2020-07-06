#include "gtest/gtest.h"

#include "math/prime/rho128.h"

namespace math {

TEST(Rho128, testSmall) {
  MontgomeryMul mont;
  EXPECT_EQ(rho128(4, mont, true, 1, 2), 2);
  EXPECT_EQ(rho128(9, mont, true, 1, 2), 3);
  EXPECT_EQ(rho128(121, mont, true, 1, 2), 11);
}

TEST(Rho128, testLarge) {
  MontgomeryMul mont;

  __uint128_t v = rho128(2 * 1000000007ULL, mont, true, 1, 2);
  EXPECT_TRUE(v == 2 || v == 1000000007);

  EXPECT_EQ(rho128(1000000007 * 1000000007ULL, mont, true, 1, 2), 1000000007);

  v = rho128(
      __uint128_t(9616562014629204ULL) * 100000000000000ULL + 97194293996611ULL,
      mont,
      true,
      1,
      2);
  EXPECT_TRUE(
      v == 973825889 || v == __uint128_t(98750322036562790) * 10000 + 2499);

  v = rho128(
      __uint128_t(9553427693635611ULL) * 100000000000000ULL + 1863533963531ULL,
      mont,
      true,
      1,
      2);
  EXPECT_TRUE(v == 973806882626147ULL || v == 981039245468473ULL);

  v = rho128(
      __uint128_t(9637823792045106ULL) * 100000000000000ULL + 91122291047909ULL,
      mont,
      true,
      1,
      2);
  EXPECT_TRUE(v == 244564652505673ULL || v == 3940808163935933ULL);
}

} // namespace math
