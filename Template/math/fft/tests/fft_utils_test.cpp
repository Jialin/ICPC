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

TEST(FFTUtilsTest, recurrenceInlineModJetpack) {
  const int MOD = 1000000007;
  FFTUtils<> fft;
  vector<ModInt<int, int64_t, MOD>> bases, res;

  bases = {0, 1, 1, 0, 1, 0, 2, 0, 5};
  res = {1};
  fft.recurrenceInlineMod(res, bases, 1, 10000, [](int& f, int idx) {});
  ASSERT_GE(10000, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(1, res[1]._v);
  EXPECT_EQ(2, res[2]._v);
  EXPECT_EQ(3, res[3]._v);
  EXPECT_EQ(6, res[4]._v);
  EXPECT_EQ(10, res[5]._v);
  EXPECT_EQ(20, res[6]._v);
  EXPECT_EQ(35, res[7]._v);
  EXPECT_EQ(50622761, res[1024]._v);
  EXPECT_EQ(294060367, res[1025]._v);
  EXPECT_EQ(600102449, res[2048]._v);
  EXPECT_EQ(894517855, res[2049]._v);
  EXPECT_EQ(200542943, res[4096]._v);
  EXPECT_EQ(911015404, res[4097]._v);
}

} // namespace math
