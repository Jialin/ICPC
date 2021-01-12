#include "gtest/gtest.h"

#define FFT_MUL_UTILS_ALL
#include "math/fft/fft_mul_utils_macros.h"

#include "math/fft/fft_mul_utils.h"

namespace math {

namespace {

constexpr double EPS = 1E-12;
constexpr double LARGE_EPS = 0.1;

} // namespace

TEST(FFTMulUtilsTest, mulInt) {
  auto& fft = FFTMulUtils<>::instance();
  vector<int> xs, ys;

  xs = {3, 4};
  ys = {};
  const auto& res1 = fft.mulInt(xs, ys, false);
  ASSERT_EQ(1, res1.size());
  EXPECT_NEAR(0, res1[0].real, EPS);
  EXPECT_NEAR(0, res1[0].real, EPS);
  EXPECT_NEAR(0, res1[0].imag, EPS);

  xs = {0, 0};
  ys = {3, 4};
  const auto& res2 = fft.mulInt(xs, ys, false);
  ASSERT_EQ(1, res2.size());
  EXPECT_NEAR(0, res2[0].real, EPS);
  EXPECT_NEAR(0, res2[0].imag, EPS);

  xs = {1, 2};
  ys = {3, 4};
  const auto& res3 = fft.mulInt(xs, ys, false);
  ASSERT_EQ(3, res3.size());
  EXPECT_NEAR(3, res3[0].real, EPS);
  EXPECT_NEAR(0, res3[0].imag, EPS);
  EXPECT_NEAR(10, res3[1].real, EPS);
  EXPECT_NEAR(0, res3[1].imag, EPS);
  EXPECT_NEAR(8, res3[2].real, EPS);
  EXPECT_NEAR(0, res3[2].imag, EPS);

  xs = {31772, 371773, 371721, 81631};
  ys = {348484, 28481838, 381872, 59492};
  const auto& res4 = fft.mulInt(xs, ys, false);
  ASSERT_EQ(7, res4.size());
  EXPECT_NEAR(11072033648, res4[0].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[0].imag, LARGE_EPS);
  EXPECT_NEAR(1034481899068, res4[1].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[1].imag, LARGE_EPS);
  EXPECT_NEAR(10730450016922, res4[2].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[2].imag, LARGE_EPS);
  EXPECT_NEAR(10759604279482, res4[3].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[3].imag, LARGE_EPS);
  EXPECT_NEAR(2489068278806, res4[4].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[4].imag, LARGE_EPS);
  EXPECT_NEAR(53287018964, res4[5].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[5].imag, LARGE_EPS);
  EXPECT_NEAR(4856391452, res4[6].real, LARGE_EPS);
  EXPECT_NEAR(0, res4[6].imag, LARGE_EPS);

  xs = {1, 2};
  ys = {3, 4, 5, 6};
  const auto& res5 = fft.mulInt(xs, ys, true);
  EXPECT_EQ(4, res5.size());
  EXPECT_NEAR(15, res5[0].real, EPS);
  EXPECT_NEAR(0, res5[0].imag, EPS);
  EXPECT_NEAR(10, res5[1].real, EPS);
  EXPECT_NEAR(0, res5[1].imag, EPS);
  EXPECT_NEAR(13, res5[2].real, EPS);
  EXPECT_NEAR(0, res5[2].imag, EPS);
  EXPECT_NEAR(16, res5[3].real, EPS);
  EXPECT_NEAR(0, res5[3].imag, EPS);

  xs = {1, 2};
  ys = {3, 4, 5, 6, 7};
  const auto& res6 = fft.mulInt(xs, ys, true);
  EXPECT_EQ(6, res6.size());
  EXPECT_NEAR(3, res6[0].real, EPS);
  EXPECT_NEAR(0, res6[0].imag, EPS);
  EXPECT_NEAR(10, res6[1].real, EPS);
  EXPECT_NEAR(0, res6[1].imag, EPS);
  EXPECT_NEAR(13, res6[2].real, EPS);
  EXPECT_NEAR(0, res6[2].imag, EPS);
  EXPECT_NEAR(16, res6[3].real, EPS);
  EXPECT_NEAR(0, res6[3].imag, EPS);
  EXPECT_NEAR(19, res6[4].real, EPS);
  EXPECT_NEAR(0, res6[4].imag, EPS);
  EXPECT_NEAR(14, res6[5].real, EPS);
  EXPECT_NEAR(0, res6[5].imag, EPS);
}

TEST(FFTMulUtilsTest, mulInlineInt) {
  auto& fft = FFTMulUtils<>::instance();
  vector<int> xs, ys;

  xs = {3, 4};
  ys = {};
  fft.mulInlineInt(xs, ys, false);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]);

  xs = {0, 0};
  ys = {3, 4};
  fft.mulInlineInt(xs, ys, false);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]);

  xs = {1, 2};
  ys = {3, 4};
  fft.mulInlineInt(xs, ys, false);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(8, xs[2]);

  vector<int64_t> xs64, ys64;
  xs64 = {31772, 371773, 371721, 81631};
  ys64 = {348484, 28481838, 381872, 59492};
  fft.mulInlineInt(xs64, ys64, false);
  ASSERT_EQ(7, xs64.size());
  EXPECT_EQ(11072033648, xs64[0]);
  EXPECT_EQ(1034481899068, xs64[1]);
  EXPECT_EQ(10730450016922, xs64[2]);
  EXPECT_EQ(10759604279482, xs64[3]);
  EXPECT_EQ(2489068278806, xs64[4]);
  EXPECT_EQ(53287018964, xs64[5]);
  EXPECT_EQ(4856391452, xs64[6]);

  xs = {1, 2};
  ys = {3, 4, 5, 6};
  fft.mulInlineInt(xs, ys, true);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(15, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(13, xs[2]);
  EXPECT_EQ(16, xs[3]);

  xs = {1, 2};
  ys = {3, 4, 5, 6, 7};
  fft.mulInlineInt(xs, ys, true);
  ASSERT_EQ(6, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(13, xs[2]);
  EXPECT_EQ(16, xs[3]);
  EXPECT_EQ(19, xs[4]);
  EXPECT_EQ(14, xs[5]);
}

} // namespace math
