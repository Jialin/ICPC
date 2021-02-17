#include "gtest/gtest.h"

#define MOD_INT_DIV_INLINE
#define NTT_POLY_MOD_INT_ALL
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "math/poly/ntt_poly_mod_int.h"

namespace math {

TEST(NTTPolyModIntTest, mulInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> xs, ys;

  xs = vector<int>{1, 2, 3};
  ys = vector<int>{0, 0};
  xs *= ys;
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]._v);

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
  EXPECT_EQ(3263884, xs[0]._v);
  EXPECT_EQ(7008180, xs[1]._v);
  EXPECT_EQ(4393991, xs[2]._v);
  EXPECT_EQ(4045475, xs[3]._v);
  EXPECT_EQ(4368242, xs[4]._v);
  EXPECT_EQ(5719417, xs[5]._v);
  EXPECT_EQ(4629639, xs[6]._v);
}

TEST(NTTPolyModIntTest, divInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> xs, ys;
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

TEST(NTTPolyModIntTest, modInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> xs, ys;
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

TEST(NTTPolyModIntTest, recurrence) {
  const int MOD = 104857601;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 21> xs, coefs;
  xs = vector<int>{1, 2, 3};
  coefs = vector<int>{6, 5, 4};
  EXPECT_EQ(1, coefs.recurrence(xs, 0)._v);
  EXPECT_EQ(2, coefs.recurrence(xs, 1)._v);
  EXPECT_EQ(3, coefs.recurrence(xs, 2)._v);
  EXPECT_EQ(28, coefs.recurrence(xs, 3)._v);
  EXPECT_EQ(139, coefs.recurrence(xs, 4)._v);
  EXPECT_EQ(2690515, coefs.recurrence(xs, 10)._v);
  EXPECT_EQ(35593197, coefs.recurrence(xs, 100)._v);
  EXPECT_EQ(33015477, coefs.recurrence(xs, 1000)._v);
  EXPECT_EQ(99777528, coefs.recurrence(xs, 100000000000000)._v);
}

TEST(NTTPolyModIntTest, mulInlineCyclic) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> xs, ys;
  xs = vector<int>{135624671, 381862};
  ys = vector<int>{356513, 125683, 1215655};
  xs.mulInlineCyclic(ys);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(4747033, xs[0]._v);
  EXPECT_EQ(4104746, xs[1]._v);
  EXPECT_EQ(1700042, xs[2]._v);
  EXPECT_EQ(6742591, xs[3]._v);
}

TEST(NTTPolyModIntTest, inv) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> xs;
  xs = vector<int>{1, 7340032, 7340032, 0, 7340032, 0, 7340031, 0, 0, 0, 0};
  const auto& res1 = xs.inv();
  ASSERT_EQ(11, res1.size());
  EXPECT_EQ(1, res1[0]._v);
  EXPECT_EQ(1, res1[1]._v);
  EXPECT_EQ(2, res1[2]._v);
  EXPECT_EQ(3, res1[3]._v);
  EXPECT_EQ(6, res1[4]._v);
  EXPECT_EQ(10, res1[5]._v);
  EXPECT_EQ(20, res1[6]._v);
  EXPECT_EQ(35, res1[7]._v);
  EXPECT_EQ(65, res1[8]._v);
  EXPECT_EQ(116, res1[9]._v);
  EXPECT_EQ(213, res1[10]._v);

  xs = vector<int>{1, 3670016, 3670016, 0, 0};
  const auto& res2 = xs.inv();
  ASSERT_EQ(5, res2.size());
  EXPECT_EQ(1, res2[0]._v);
  EXPECT_EQ(3670017, res2[1]._v);
  EXPECT_EQ(1835009, res2[2]._v);
  EXPECT_EQ(2752513, res2[3]._v);
  EXPECT_EQ(2293761, res2[4]._v);

  xs = vector<int>{1, 3909610, 2898993, 2898993, 1347489, 1292920};
  const auto& res3 = xs.inv();
  ASSERT_EQ(6, res3.size());
  EXPECT_EQ(1, res3[0]._v);
  EXPECT_EQ(3430423, res3[1]._v);
  EXPECT_EQ(1253181, res3[2]._v);
  EXPECT_EQ(1705603, res3[3]._v);
  EXPECT_EQ(4560677, res3[4]._v);
  EXPECT_EQ(1508198, res3[5]._v);
}

TEST(NTTPolyModIntTest, invInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> res;
  res = vector<int>{1, 0};
  res.invInline();
  ASSERT_EQ(2, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(0, res[1]._v);

  res = vector<int>{1, 7340032, 7340032, 0, 7340032, 0, 7340031, 0, 0, 0, 0};
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

  res = vector<int>{1, 3670016, 3670016, 0, 0};
  res.invInline();
  ASSERT_EQ(5, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(3670017, res[1]._v);
  EXPECT_EQ(1835009, res[2]._v);
  EXPECT_EQ(2752513, res[3]._v);
  EXPECT_EQ(2293761, res[4]._v);

  res = vector<int>{1, 3909610, 2898993, 2898993, 1347489, 1292920};
  res.invInline();
  ASSERT_EQ(6, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(3430423, res[1]._v);
  EXPECT_EQ(1253181, res[2]._v);
  EXPECT_EQ(1705603, res[3]._v);
  EXPECT_EQ(4560677, res[4]._v);
  EXPECT_EQ(1508198, res[5]._v);
}

TEST(NTTPolyModIntTest, expInline) {
  const int MOD = 924844033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 3597> res;
  res = vector<int>{0, 0, 1, 3, 616562698};
  res.expInline();
  ASSERT_EQ(5, res.size());
  EXPECT_EQ(1, res[0]._v);
  EXPECT_EQ(0, res[1]._v);
  EXPECT_EQ(1, res[2]._v);
  EXPECT_EQ(3, res[3]._v);
  EXPECT_EQ(154140682, res[4]._v);
}

TEST(NTTPolyModIntTest, deriveInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> res;
  res = vector<int>{1283, 1331, 14322, 112315, 1812};
  res.deriveInline();
  ASSERT_EQ(4, res.size());
  EXPECT_EQ(1331, res[0]._v);
  EXPECT_EQ(28644, res[1]._v);
  EXPECT_EQ(336945, res[2]._v);
  EXPECT_EQ(7248, res[3]._v);
}

TEST(NTTPolyModIntTest, integralInline) {
  const int MOD = 7340033;
  NTTPolyModInt<ModInt<int, int64_t, MOD>, 5> res;
  res = vector<int>{12, 13, 14, 15};
  res.integralInline();
  ASSERT_EQ(5, res.size());
  EXPECT_EQ(0, res[0]._v);
  EXPECT_EQ(12, res[1]._v);
  EXPECT_EQ(3670023, res[2]._v);
  EXPECT_EQ(4893360, res[3]._v);
  EXPECT_EQ(1835012, res[4]._v);
}

TEST(NTTPolyModIntTest, onlineInline) {
  const int MOD = 924844033;
  using ModInt = ModInt<int, int64_t, MOD>;
  NTTPolyModInt<ModInt, 3597> fs, bases;

  fs = vector<int>{1};
  bases = vector<int>{0, 0, 2, 9, 616562726, 693633181, 739875896, 161850647, 346462722, 125987923};
  fs.onlineInline(bases, 1, 10, [](ModInt& f, int idx) {
    f /= idx;
  });
  ASSERT_GE(fs.size(), 10);
  EXPECT_EQ(1, fs[0]._v);
  EXPECT_EQ(0, fs[1]._v);
  EXPECT_EQ(1, fs[2]._v);
  EXPECT_EQ(3, fs[3]._v);
  EXPECT_EQ(154140682, fs[4]._v);
  EXPECT_EQ(693633059, fs[5]._v);
  EXPECT_EQ(739875352, fs[6]._v);
  EXPECT_EQ(254332590, fs[7]._v);
  EXPECT_EQ(76705244, fs[8]._v);
  EXPECT_EQ(34551843, fs[9]._v);

  fs = vector<int>{1};
  bases = vector<int>{
      0, 1, 1, 462422018, 308281347, 732168198, 369937624, 52664753, 358193614, 161641386};
  fs.onlineInline(bases, 1, 10, [](ModInt& f, int idx) {
    f /= idx;
  });
  ASSERT_GE(fs.size(), 10);
  EXPECT_EQ(1, fs[0]._v);
  EXPECT_EQ(1, fs[1]._v);
  EXPECT_EQ(1, fs[2]._v);
  EXPECT_EQ(770703362, fs[3]._v);
  EXPECT_EQ(385351682, fs[4]._v);
  EXPECT_EQ(716754128, fs[5]._v);
  EXPECT_EQ(303143326, fs[6]._v);
  EXPECT_EQ(246441582, fs[7]._v);
  EXPECT_EQ(612984437, fs[8]._v);
  EXPECT_EQ(547380366, fs[9]._v);
}

} // namespace math
