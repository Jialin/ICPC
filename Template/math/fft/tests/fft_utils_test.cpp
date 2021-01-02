#include "gtest/gtest.h"

#define BIGINT_ALL
#define FFT_UTILS_ALL
#include "math/fft/fft_utils_macros.h"

#include "math/fft/fft_utils.h"

namespace math {

TEST(FFTUtilsTest, bigint) {
  FFTUtils<> fft;
  BigInt<4, int> x, y, res;
  x = "0";
  y = "0";
  fft.mul(x, y, res);
  ASSERT_EQ(1, res._vs.size());
  EXPECT_EQ(0, res._vs[0]);

  x = "1";
  y = "0";
  fft.mul(x, y, res);
  ASSERT_EQ(1, res._vs.size());
  EXPECT_EQ(0, res._vs[0]);

  x = "1833811";
  y = "0";
  fft.mul(x, y, res);
  ASSERT_EQ(1, res._vs.size());
  EXPECT_EQ(0, res._vs[0]);

  x = "12";
  y = "77";
  fft.mul(x, y, res);
  ASSERT_EQ(1, res._vs.size());
  EXPECT_EQ(924, res._vs[0]);

  x = "1833811";
  y = "1847182";
  fft.mul(x, y, res);
  ASSERT_EQ(4, res._vs.size());
  EXPECT_EQ(602, res._vs[0]);
  EXPECT_EQ(8267, res._vs[1]);
  EXPECT_EQ(3873, res._vs[2]);
  EXPECT_EQ(3, res._vs[3]);

  x = "12";
  y = "77";
  fft.mul(x, y, res);
  ASSERT_EQ(1, res._vs.size());
  EXPECT_EQ(924, res._vs[0]);
}

TEST(FFTUtilsTest, mulInlineMod) {
  FFTUtils<> fft;
  vector<int> xs = {1, 2}, ys = {3, 4};
  fft.mulInlineMod(xs, ys, 1000000007);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(8, xs[2]);

  xs = {31772, 371773, 371721, 81631};
  ys = {348484, 28481838, 381872, 59492};
  fft.mulInlineMod(xs, ys, 1000000007);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(72033571, xs[0]);
  EXPECT_EQ(481891830, xs[1]);
  EXPECT_EQ(449941812, xs[2]);
  EXPECT_EQ(604204169, xs[3]);
  EXPECT_EQ(68261383, xs[4]);
  EXPECT_EQ(287018593, xs[5]);
  EXPECT_EQ(856391424, xs[6]);
}

} // namespace math
