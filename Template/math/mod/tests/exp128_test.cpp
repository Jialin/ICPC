#include "gtest/gtest.h"

#include "math/mod/exp128.h"

namespace math {

TEST(Exp128, testSmall) {
  MontgomeryMul mont(5);
  __uint128_t v = mont.revert(exp128(mont, mont.convert(2), 3));
  EXPECT_EQ(v, 3);

  mont.init(13);
  v = mont.revert(exp128(mont, mont.convert(2), 2147483647));
  EXPECT_EQ(v, 11);

  mont.init(29477);
  v = mont.revert(exp128(mont, mont.convert(1463), 1397372724));
  EXPECT_EQ(v, 28518);
}

TEST(Exp128, testLarge) {
  __uint128_t mod = __uint128_t(172736151392837ULL) * 10000000 + 1111121;
  __uint128_t base = __uint128_t(1183471746182387ULL) * 1000000 + 182371;
  __uint128_t exp = __uint128_t(1726315516271823471ULL) * 10000000 + 6237481;
  MontgomeryMul mont(mod);
  __uint128_t v = mont.revert(exp128(mont, mont.convert(base), exp));

  __uint128_t expect = __uint128_t(15288318436767191ULL) * 100000 + 35375;
  EXPECT_EQ(v, expect);
}

} // namespace math
