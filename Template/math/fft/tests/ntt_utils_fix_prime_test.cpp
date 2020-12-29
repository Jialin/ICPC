#include "gtest/gtest.h"

#define NTT_UTILS_FIX_PRIME_ALL
#include "math/fft/ntt_utils_fix_prime_macros.h"

#include "math/fft/ntt_utils_fix_prime.h"

namespace math {

TEST(NTTUtilsFixPrimeTest, bigint) {
  NTTUtilsFixPrime<int, int64_t, 7340033, 5> ntt;
  vector<ModInt<int, int64_t, 7340033>> x = {1, 2}, y = {3, 4};
  ntt.mulInline(x, y);
  ASSERT_EQ(3, x.size());
  EXPECT_EQ(3, x[0]._v);
  EXPECT_EQ(10, x[1]._v);
  EXPECT_EQ(8, x[2]._v);

  x = {31772, 371773, 371721, 81631};
  y = {348484, 28481838, 381872, 59492};
  ntt.mulInline(x, y);
  ASSERT_EQ(7, x.size());
  EXPECT_EQ(3263884, x[0]._v);
  EXPECT_EQ(7008180, x[1]._v);
  EXPECT_EQ(4393991, x[2]._v);
  EXPECT_EQ(4045475, x[3]._v);
  EXPECT_EQ(4368242, x[4]._v);
  EXPECT_EQ(5719417, x[5]._v);
  EXPECT_EQ(4629639, x[6]._v);
}

} // namespace math
