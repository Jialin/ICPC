#include "gtest/gtest.h"

#define NTT_MUL_UTILS_ALL
#include "math/fft/ntt_mul_utils_macros.h"

#include "math/fft/ntt_mul_utils.h"

namespace math {

TEST(NTTMulUtilsTest, mulInlineModInt) {
  const int MOD = 7340033;
  vector<ModInt<int, int64_t, MOD>> xs = {1, 2}, ys = {3, 4};
  NTTMulUtils<int, int64_t, MOD, 5>::instance().mulInlineModInt(xs, ys, false);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]._v);
  EXPECT_EQ(10, xs[1]._v);
  EXPECT_EQ(8, xs[2]._v);

  xs = {31772, 371773, 371721, 81631};
  ys = {348484, 28481838, 381872, 59492};
  NTTMulUtils<int, int64_t, MOD, 5>::instance().mulInlineModInt(xs, ys, false);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(3263884, xs[0]._v);
  EXPECT_EQ(7008180, xs[1]._v);
  EXPECT_EQ(4393991, xs[2]._v);
  EXPECT_EQ(4045475, xs[3]._v);
  EXPECT_EQ(4368242, xs[4]._v);
  EXPECT_EQ(5719417, xs[5]._v);
  EXPECT_EQ(4629639, xs[6]._v);

  xs = {1, 2, 3, 4};
  NTTMulUtils<int, int64_t, MOD, 5>::instance().mulInlineModInt(xs, xs, false);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(1, xs[0]._v);
  EXPECT_EQ(4, xs[1]._v);
  EXPECT_EQ(10, xs[2]._v);
  EXPECT_EQ(20, xs[3]._v);
  EXPECT_EQ(25, xs[4]._v);
  EXPECT_EQ(24, xs[5]._v);
  EXPECT_EQ(16, xs[6]._v);
}

TEST(NTTMulUtilsTest, mulInlineModIntCyclic) {
  const int MOD = 104857601;
  vector<ModInt<int, int64_t, MOD>> xs = {4, 1}, ys = {104857595, 104857596, 104857597, 1};
  NTTMulUtils<int, int64_t, MOD, 21>::instance().mulInlineModInt(xs, ys, true);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(104857578, xs[0]._v);
  EXPECT_EQ(104857575, xs[1]._v);
  EXPECT_EQ(104857580, xs[2]._v);
}

} // namespace math
