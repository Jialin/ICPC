#include "gtest/gtest.h"

#define FFT_MUL_MOD_UTILS_ALL
#define FFT_POLY_MOD_INT_ASSIGN_VECTOR
#include "math/fft/fft_mul_mod_utils_macros.h"
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/fft/fft_mul_mod_utils.h"
#include "math/poly/fft_poly_mod_int.h"

using namespace std;

namespace math {

TEST(FFTMulModUtilsTest, mulInlineModInt) {
  auto& fft = FFTMulModUtils<double>::instance();
  FFTPolyModInt<double, ModInt<int, int64_t, 1000000007>> xs, ys;
  xs = vector<int>{1, 2};
  ys = vector<int>{3, 4};
  fft.mulInlineModInt(xs, ys, false);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]._v);
  EXPECT_EQ(10, xs[1]._v);
  EXPECT_EQ(8, xs[2]._v);

  xs = vector<int>{31772, 371773, 371721, 81631};
  ys = vector<int>{348484, 28481838, 381872, 59492};
  fft.mulInlineModInt(xs, ys, false);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(72033571, xs[0]._v);
  EXPECT_EQ(481891830, xs[1]._v);
  EXPECT_EQ(449941812, xs[2]._v);
  EXPECT_EQ(604204169, xs[3]._v);
  EXPECT_EQ(68261383, xs[4]._v);
  EXPECT_EQ(287018593, xs[5]._v);
  EXPECT_EQ(856391424, xs[6]._v);
}

} // namespace math
