#include "gtest/gtest.h"

#define MOD_INT_DIV_INLINE
#define NTT_POLY_MOD_INT_ALL
#include "math/poly/ntt_poly_mod_int_macros.h"

#include "math/poly/ntt_poly_mod_int.h"

namespace math {

TEST(NTTPolyModIntTest, mulInline) {
  const int MOD = 7340033;
  NTTPolyModInt<int, int64_t, MOD, 5> xs, ys;

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

TEST(NTTPolyModIntTest, mulInlineCyclic) {
  const int MOD = 7340033;
  NTTPolyModInt<int, int64_t, MOD, 5> xs, ys;
  xs = vector<int>{135624671, 381862};
  ys = vector<int>{356513, 125683, 1215655};
  xs.mulInlineCyclic(ys);
  ASSERT_EQ(4, xs.size());
  EXPECT_EQ(4747033, xs[0]._v);
  EXPECT_EQ(4104746, xs[1]._v);
  EXPECT_EQ(1700042, xs[2]._v);
  EXPECT_EQ(6742591, xs[3]._v);
}

TEST(NTTPolyModIntTest, onlineInline) {
  const int MOD = 924844033;
  auto& ntt = NTTOnlineUtils<int, int64_t, MOD, 3597>::instance();
  NTTPolyModInt<int, int64_t, MOD, 3597> fs, bases;

  fs = vector<int>{1};
  bases = vector<int>{0, 0, 2, 9, 616562726, 693633181, 739875896, 161850647, 346462722, 125987923};
  fs.onlineInline(bases, 1, 10, [](ModInt<int, int64_t, MOD>& f, int idx) {
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
  fs.onlineInline(bases, 1, 10, [](ModInt<int, int64_t, MOD>& f, int idx) {
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
