#include "gtest/gtest.h"

#define FFT_MUL_UTILS_ALL
#include "math/fft/fft_mul_utils_macros.h"

#include "math/fft/fft_mul_utils.h"

namespace math {

namespace {

constexpr double EPS = 1E-12;
constexpr double LARGE_EPS = 0.1;

} // namespace

TEST(FFTMulUtilsTest, mulReal) {
  auto& fft = FFTMulUtils<>::instance();
  vector<int> xs, ys;

  xs = {3, 4};
  ys = {};
  const auto& res1 = fft.mulReal(xs, ys, false);
  ASSERT_EQ(1, res1.size());
  EXPECT_NEAR(0, res1[0].real, EPS);
  EXPECT_NEAR(0, res1[0].real, EPS);
  EXPECT_NEAR(0, res1[0].imag, EPS);

  xs = {0, 0};
  ys = {3, 4};
  const auto& res2 = fft.mulReal(xs, ys, false);
  ASSERT_EQ(1, res2.size());
  EXPECT_NEAR(0, res2[0].real, EPS);
  EXPECT_NEAR(0, res2[0].imag, EPS);

  xs = {1, 2};
  ys = {3, 4};
  const auto& res3 = fft.mulReal(xs, ys, false);
  ASSERT_EQ(3, res3.size());
  EXPECT_NEAR(3, res3[0].real, EPS);
  EXPECT_NEAR(0, res3[0].imag, EPS);
  EXPECT_NEAR(10, res3[1].real, EPS);
  EXPECT_NEAR(0, res3[1].imag, EPS);
  EXPECT_NEAR(8, res3[2].real, EPS);
  EXPECT_NEAR(0, res3[2].imag, EPS);

  xs = {31772, 371773, 371721, 81631};
  ys = {348484, 28481838, 381872, 59492};
  const auto& res4 = fft.mulReal(xs, ys, false);
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
  const auto& res5 = fft.mulReal(xs, ys, true);
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
  const auto& res6 = fft.mulReal(xs, ys, true);
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

  vector<double> xsR = {1, 2}, ysR = {3, 4, 5, 6, 7};
  const auto& res7 = fft.mulReal(xsR, ysR, true);
  EXPECT_EQ(8, res7.size());
  EXPECT_NEAR(3, res7[0].real, EPS);
  EXPECT_NEAR(0, res7[0].imag, EPS);
  EXPECT_NEAR(10, res7[1].real, EPS);
  EXPECT_NEAR(0, res7[1].imag, EPS);
  EXPECT_NEAR(13, res7[2].real, EPS);
  EXPECT_NEAR(0, res7[2].imag, EPS);
  EXPECT_NEAR(16, res7[3].real, EPS);
  EXPECT_NEAR(0, res7[3].imag, EPS);
  EXPECT_NEAR(19, res7[4].real, EPS);
  EXPECT_NEAR(0, res7[4].imag, EPS);
  EXPECT_NEAR(14, res7[5].real, EPS);
  EXPECT_NEAR(0, res7[5].imag, EPS);
  EXPECT_NEAR(0, res7[6].real, EPS);
  EXPECT_NEAR(0, res7[6].imag, EPS);
  EXPECT_NEAR(0, res7[7].real, EPS);
  EXPECT_NEAR(0, res7[7].imag, EPS);
}

TEST(FFTMulUtilsTest, mulInlineReal) {
  auto& fft = FFTMulUtils<>::instance();
  vector<int> xs, ys;

  xs = {3, 4};
  ys = {};
  fft.mulInlineReal(xs, ys, false);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]);

  xs = {0, 0};
  ys = {3, 4};
  fft.mulInlineReal(xs, ys, false);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]);

  xs = {1, 2};
  ys = {3, 4};
  fft.mulInlineReal(xs, ys, false);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(8, xs[2]);

  vector<int64_t> xs64, ys64;
  xs64 = {31772, 371773, 371721, 81631};
  ys64 = {348484, 28481838, 381872, 59492};
  fft.mulInlineReal(xs64, ys64, false);
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
  fft.mulInlineReal(xs, ys, true);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(15, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(13, xs[2]);
  EXPECT_EQ(16, xs[3]);

  xs = {1, 2};
  ys = {3, 4, 5, 6, 7};
  fft.mulInlineReal(xs, ys, true);
  ASSERT_EQ(6, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(13, xs[2]);
  EXPECT_EQ(16, xs[3]);
  EXPECT_EQ(19, xs[4]);
  EXPECT_EQ(14, xs[5]);

  vector<double> xsR = {1, 2}, ysR = {3, 4, 5, 6, 7};
  fft.mulInlineReal(xsR, ysR, true);
  ASSERT_EQ(8, xsR.size());
  EXPECT_NEAR(3, xsR[0], EPS);
  EXPECT_NEAR(10, xsR[1], EPS);
  EXPECT_NEAR(13, xsR[2], EPS);
  EXPECT_NEAR(16, xsR[3], EPS);
  EXPECT_NEAR(19, xsR[4], EPS);
  EXPECT_NEAR(14, xsR[5], EPS);
  EXPECT_NEAR(0, xsR[6], EPS);
  EXPECT_NEAR(0, xsR[7], EPS);
}

TEST(FFTMulUtilsTest, mulInlineModify2d) {
  auto& fft = FFTMulUtils<double>::instance();
  vector<vector<Complex<double>>> xs, ys;
  xs = {
      {{1, 0}, {2, 0}, {3, 0}},
      {{4, 0}, {5, 0}, {6, 0}},
      {{7, 0}, {8, 0}, {9, 0}}};
  ys = {{{10, 0}, {11, 0}}, {{12, 0}, {13, 0}}};
  fft.mulInlineModify2d(xs, ys, false);
  ASSERT_EQ(4, xs.size());
  ASSERT_EQ(4, xs[0].size());
  EXPECT_NEAR(10, xs[0][0].real, EPS);
  EXPECT_NEAR(0, xs[0][0].imag, EPS);
  EXPECT_NEAR(31, xs[0][1].real, EPS);
  EXPECT_NEAR(0, xs[0][1].imag, EPS);
  EXPECT_NEAR(52, xs[0][2].real, EPS);
  EXPECT_NEAR(0, xs[0][2].imag, EPS);
  EXPECT_NEAR(33, xs[0][3].real, EPS);
  EXPECT_NEAR(0, xs[0][3].imag, EPS);
  ASSERT_EQ(4, xs[1].size());
  EXPECT_NEAR(52, xs[1][0].real, EPS);
  EXPECT_NEAR(0, xs[1][0].imag, EPS);
  EXPECT_NEAR(131, xs[1][1].real, EPS);
  EXPECT_NEAR(0, xs[1][1].imag, EPS);
  EXPECT_NEAR(177, xs[1][2].real, EPS);
  EXPECT_NEAR(0, xs[1][2].imag, EPS);
  EXPECT_NEAR(105, xs[1][3].real, EPS);
  EXPECT_NEAR(0, xs[1][3].imag, EPS);
  ASSERT_EQ(4, xs[2].size());
  EXPECT_NEAR(118, xs[2][0].real, EPS);
  EXPECT_NEAR(0, xs[2][0].imag, EPS);
  EXPECT_NEAR(269, xs[2][1].real, EPS);
  EXPECT_NEAR(0, xs[2][1].imag, EPS);
  EXPECT_NEAR(315, xs[2][2].real, EPS);
  EXPECT_NEAR(0, xs[2][2].imag, EPS);
  EXPECT_NEAR(177, xs[2][3].real, EPS);
  EXPECT_NEAR(0, xs[2][3].imag, EPS);
  ASSERT_EQ(4, xs[3].size());
  EXPECT_NEAR(84, xs[3][0].real, EPS);
  EXPECT_NEAR(0, xs[3][0].imag, EPS);
  EXPECT_NEAR(187, xs[3][1].real, EPS);
  EXPECT_NEAR(0, xs[3][1].imag, EPS);
  EXPECT_NEAR(212, xs[3][2].real, EPS);
  EXPECT_NEAR(0, xs[3][2].imag, EPS);
  EXPECT_NEAR(117, xs[3][3].real, EPS);
  EXPECT_NEAR(0, xs[3][3].imag, EPS);
}

} // namespace math
