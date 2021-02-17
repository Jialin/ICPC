#include "gtest/gtest.h"

#define FFT_POLY_MOD_INT_ALL
#include "math/poly/fft_poly_mod_int_macros.h"

#include "math/poly/fft_poly_mod_int.h"

using namespace std;

namespace math {

TEST(FFTPolyModIntTest, mulInline) {
  FFTPolyModInt<double, ModInt<int, int64_t, 1000000007>> xs, ys;
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
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> bases, res;
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

TEST(FFTPolyModIntTest, invInline) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> res;
  res = vector<int>{1, 1000000006, 1000000006, 0, 1000000006, 0, 1000000005, 0, 0, 0, 0};
  res.invInline();
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

  res = vector<int>{1, 500000003, 500000003, 0, 0};
  res.invInline();
  ASSERT_EQ(5, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(500000004, res[1]._v);
  EXPECT_EQ(750000006, res[2]._v);
  EXPECT_EQ(625000005, res[3]._v);
  EXPECT_EQ(187500002, res[4]._v);

  res = vector<int>{1, 833333339, 722222227, 722222227, 148148149, 478395065};
  res.invInline();
  ASSERT_EQ(6, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(166666668, res[1]._v);
  EXPECT_EQ(305555558, res[2]._v);
  EXPECT_EQ(375000003, res[3]._v);
  EXPECT_EQ(101080248, res[4]._v);
  EXPECT_EQ(925025727, res[5]._v);
}

TEST(FFTPolyModIntTest, recurrence) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> coefs, xs;
  coefs = vector<int>{1, 1};
  xs = vector<int>{1, 1};
  EXPECT_EQ(55, coefs.recurrence(xs, 9)._v);

  coefs = vector<int>{1, 1, 1};
  xs = vector<int>{1, 1, 1};
  EXPECT_EQ(105, coefs.recurrence(xs, 9)._v);
  EXPECT_EQ(193, coefs.recurrence(xs, 10)._v);
  EXPECT_EQ(166924950, coefs.recurrence(xs, 100)._v);
  EXPECT_EQ(430943869, coefs.recurrence(xs, 1000)._v);
  EXPECT_EQ(65299825, coefs.recurrence(xs, 10000)._v);
}

TEST(FFTPolyModIntTest, divInline) {
  const int MOD = 7340033;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> xs, ys;
  xs = vector<int>{15, 22, 27, 18};
  ys = vector<int>{2, 3};
  xs /= ys;
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(4, xs[0]._v);
  EXPECT_EQ(5, xs[1]._v);
  EXPECT_EQ(6, xs[2]._v);

  xs = vector<int>{15, 30, 27, 18};
  ys = vector<int>{4, 5, 6};
  xs /= ys;
  ASSERT_EQ(2, xs.size());
  EXPECT_EQ(2, xs[0]._v);
  EXPECT_EQ(3, xs[1]._v);
}

TEST(FFTPolyModIntTest, modInline) {
  const int MOD = 7340033;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> xs, ys;
  xs = vector<int>{15, 22, 27, 18};
  ys = vector<int>{2, 3};
  xs %= ys;
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(7, xs[0]._v);

  xs = vector<int>{15, 30, 27, 18};
  ys = vector<int>{4, 5, 6};
  xs %= ys;
  ASSERT_EQ(2, xs.size());
  EXPECT_EQ(7, xs[0]._v);
  EXPECT_EQ(8, xs[1]._v);
}

TEST(FFTPolyModIntTest, powModInline) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> baseP, modP;
  modP = vector<int>{1, 1000000005, 1000000004, 1000000002};

  baseP = vector<int>{0, 1};
  baseP.powModInline(modP, 7);
  ASSERT_EQ(3, baseP.size());
  EXPECT_EQ(296640002, baseP[0]._v);
  EXPECT_EQ(536320004, baseP[1]._v);
  EXPECT_EQ(994880007, baseP[2]._v);

  baseP = vector<int>{0, 1};
  baseP.powModInline(modP, 11);
  ASSERT_EQ(3, baseP.size());
  EXPECT_EQ(855637510, baseP[0]._v);
  EXPECT_EQ(723735557, baseP[1]._v);
  EXPECT_EQ(270944770, baseP[2]._v);

  baseP = vector<int>{0, 1};
  baseP.powModInline(modP, 13);
  ASSERT_EQ(3, baseP.size());
  EXPECT_EQ(112233739, baseP[0]._v);
  EXPECT_EQ(829721483, baseP[1]._v);
  EXPECT_EQ(410558385, baseP[2]._v);
}

TEST(FFTPolyModIntTest, initPowModMemo) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> baseP, modP, invRevModP, res;
  vector<FFTPolyModInt<double, ModInt<int, int64_t, MOD>>> memo;
  baseP = vector<int>{0, 1};
  modP = vector<int>{1, 1000000005, 1000000004, 1000000002};
  invRevModP = modP;
  reverse(invRevModP.begin(), invRevModP.end());
  invRevModP.invInline();

  res.initPowModMemo(baseP, modP, invRevModP, 7, memo);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(296640002, res[0]._v);
  EXPECT_EQ(536320004, res[1]._v);
  EXPECT_EQ(994880007, res[2]._v);

  res.initPowModMemo(baseP, modP, invRevModP, 11, memo);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(855637510, res[0]._v);
  EXPECT_EQ(723735557, res[1]._v);
  EXPECT_EQ(270944770, res[2]._v);

  res.initPowModMemo(baseP, modP, invRevModP, 13, memo);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(112233739, res[0]._v);
  EXPECT_EQ(829721483, res[1]._v);
  EXPECT_EQ(410558385, res[2]._v);
}

TEST(FFTPolyModIntTest, resultantModify) {
  const int MOD = 1000000007;
  FFTPolyModInt<double, ModInt<int, int64_t, MOD>> aP, bP;

  aP = vector<int>{2, 1};
  bP = vector<int>{MOD - 1, 0, 1};
  EXPECT_EQ(3, aP.resultantModify(bP)._v);

  aP = vector<int>{10, 20, 40, 30};
  bP = vector<int>{MOD - 1, 0, 0, 0, 1};
  EXPECT_EQ(0, aP.resultantModify(bP)._v);

  aP = vector<int>{10, 20, 40, 3};
  bP = vector<int>{MOD - 1, 0, 0, 0, 1};
  EXPECT_EQ(2343519, aP.resultantModify(bP)._v);
}

} // namespace math
