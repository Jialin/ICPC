#include "gtest/gtest.h"

#define POLY_MOD_INT_ALL
#include "math/poly/poly_mod_int_macros.h"

#include "math/poly/poly_mod_int.h"

namespace math {

TEST(PolyModIntTest, nttMulInlineModify) {
  const int MOD = 7340033;
  NTTUtilsFix<int, int64_t, MOD, 5> ntt;
  PolyModInt<int, int64_t, MOD> xs, ys;

  xs = vector<int>{1, 2, 3};
  ys = vector<int>{0, 0};
  xs.nttMulInlineModify(ys, false, ntt);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]._v);

  xs = vector<int>{1, 2};
  ys = vector<int>{3, 4};
  xs.nttMulInlineModify(ys, false, ntt);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]._v);
  EXPECT_EQ(10, xs[1]._v);
  EXPECT_EQ(8, xs[2]._v);

  xs = vector<int>{31772, 371773, 371721, 81631};
  ys = vector<int>{348484, 28481838, 381872, 59492};
  xs.nttMulInlineModify(ys, false, ntt);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(3263884, xs[0]._v);
  EXPECT_EQ(7008180, xs[1]._v);
  EXPECT_EQ(4393991, xs[2]._v);
  EXPECT_EQ(4045475, xs[3]._v);
  EXPECT_EQ(4368242, xs[4]._v);
  EXPECT_EQ(5719417, xs[5]._v);
  EXPECT_EQ(4629639, xs[6]._v);

  xs = vector<int>{135624671, 381862};
  ys = vector<int>{356513, 125683, 1215655};
  xs.nttMulInlineModify(ys, true, ntt);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(4747033, xs[0]._v);
  EXPECT_EQ(4104746, xs[1]._v);
  EXPECT_EQ(1700042, xs[2]._v);
  EXPECT_EQ(6742591, xs[3]._v);
}

TEST(PolyModIntTest, fftInv) {
  const int MOD = 1000000007;
  FFTUtils<double> fft;
  PolyModInt<int, int64_t, MOD> xs;
  xs = vector<int>{
      1, 1000000006, 1000000006, 0, 1000000006, 0, 1000000005, 0, 0, 0, 0};
  const auto& res = xs.fftInv(fft);
  ASSERT_EQ(11, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(1, res[1]._v);
  EXPECT_EQ(2, res[2]._v);
  EXPECT_EQ(3, res[3]._v);
  EXPECT_EQ(6, res[4]._v);
  EXPECT_EQ(10, res[5]._v);
  EXPECT_EQ(20, res[6]._v);
  EXPECT_EQ(35, res[7]._v);
  EXPECT_EQ(65, res[8]._v);
  EXPECT_EQ(116, res[9]._v);
  EXPECT_EQ(213, res[10]._v);
}

TEST(PolyModIntTest, fftInvInline) {
  const int MOD = 1000000007;
  FFTUtils<double> fft;
  PolyModInt<int, int64_t, MOD> xs;
  xs = vector<int>{
      1, 1000000006, 1000000006, 0, 1000000006, 0, 1000000005, 0, 0, 0, 0};
  xs.fftInvInline(fft);
  ASSERT_EQ(11, xs.size());
  EXPECT_EQ(1, xs[0]._v);
  EXPECT_EQ(1, xs[1]._v);
  EXPECT_EQ(2, xs[2]._v);
  EXPECT_EQ(3, xs[3]._v);
  EXPECT_EQ(6, xs[4]._v);
  EXPECT_EQ(10, xs[5]._v);
  EXPECT_EQ(20, xs[6]._v);
  EXPECT_EQ(35, xs[7]._v);
  EXPECT_EQ(65, xs[8]._v);
  EXPECT_EQ(116, xs[9]._v);
  EXPECT_EQ(213, xs[10]._v);
}

} // namespace math
