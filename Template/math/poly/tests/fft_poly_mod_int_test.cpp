#include "gtest/gtest.h"

#define FFT_POLY_MOD_INT_ALL
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

using namespace std;

namespace math {

TEST(FFTPolyModIntTest, mulInline) {
  FFTPolyModInt<double, int, int64_t, 1000000007> xs, ys;
  xs = vector<int>{1, 2};
  ys = vector<int>{3, 4};
  xs *= ys;
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]._v);
  EXPECT_EQ(10, xs[1]._v);
  EXPECT_EQ(8, xs[2]._v);

  xs = vector<int>{31772, 371773, 371721, 81631};
  ys = vector<int>{348484, 28481838, 381872, 59492};
  xs *= ys;
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(72033571, xs[0]._v);
  EXPECT_EQ(481891830, xs[1]._v);
  EXPECT_EQ(449941812, xs[2]._v);
  EXPECT_EQ(604204169, xs[3]._v);
  EXPECT_EQ(68261383, xs[4]._v);
  EXPECT_EQ(287018593, xs[5]._v);
  EXPECT_EQ(856391424, xs[6]._v);
}

TEST(FFTPolyModIntTest, onlineInline) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, int, int64_t, MOD> bases, res;
  bases = vector<int>{0, 1, 1, 0, 1, 0, 2, 0, 5};
  res = vector<int>{1};
  res.onlineInline(bases, 1, 10000, [](ModInt<int, int64_t, MOD>& f, int idx) {});
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
