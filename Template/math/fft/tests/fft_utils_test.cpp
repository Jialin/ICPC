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

} // namespace math
