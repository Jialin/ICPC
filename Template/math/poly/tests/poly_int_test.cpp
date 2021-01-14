#include "gtest/gtest.h"

#define POLY_INT_ALL
#include "math/poly/poly_int_macros.h"

#include "math/poly/poly_int.h"

namespace math {

TEST(PolyIntTest, mulInline) {
  FFTUtils<double> fft;
  PolyInt<int> xs, ys;

  xs = vector<int>{1, 2, 3};
  ys = vector<int>{0, 0};
  xs.mulInline(ys, false, fft);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]);

  xs = vector<int>{1, 2};
  ys = vector<int>{3, 4};
  xs.mulInline(ys, false, fft);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]);
  EXPECT_EQ(10, xs[1]);
  EXPECT_EQ(8, xs[2]);

  xs = vector<int>{131, 3812};
  ys = vector<int>{313, 1283, 121};
  xs.mulInline(ys, false, fft);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(41003, xs[0]);
  EXPECT_EQ(1361229, xs[1]);
  EXPECT_EQ(4906647, xs[2]);
  EXPECT_EQ(461252, xs[3]);

  xs = vector<int>{131, 3812};
  ys = vector<int>{313, 1283, 121};
  xs.mulInline(ys, true, fft);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(41003, xs[0]);
  EXPECT_EQ(1361229, xs[1]);
  EXPECT_EQ(4906647, xs[2]);
  EXPECT_EQ(461252, xs[3]);
}

} // namespace math