#include "gtest/gtest.h"

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

} // namespace math
