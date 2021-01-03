#include "gtest/gtest.h"

#define BIGINT_ALL
#define FFT_UTILS_ALL
#include "math/fft/fft_utils_macros.h"

#include "math/fft/fft_utils.h"

namespace math {

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
