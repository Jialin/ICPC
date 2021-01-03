#include "gtest/gtest.h"

#define POLY_MOD_INT_ALL
#include "math/poly/poly_mod_int_macros.h"

#include "math/poly/poly_mod_int.h"

namespace math {

TEST(PolyModIntTest, mulInlineModify) {
  const int MOD = 7340033;
  NTTUtilsFix<int, int64_t, MOD, 5> ntt;
  PolyModInt<int, int64_t, MOD> xs, ys;

  xs._vs = {1, 2, 3};
  ys._vs = {0, 0};
  xs.mulInlineModify(ys, ntt);
  ASSERT_EQ(1, xs.size());
  EXPECT_EQ(0, xs[0]._v);

  xs._vs = {1, 2};
  ys._vs = {3, 4};
  xs.mulInlineModify(ys, ntt);
  ASSERT_EQ(3, xs.size());
  EXPECT_EQ(3, xs[0]._v);
  EXPECT_EQ(10, xs[1]._v);
  EXPECT_EQ(8, xs[2]._v);

  xs._vs = {31772, 371773, 371721, 81631};
  ys._vs = {348484, 28481838, 381872, 59492};
  xs.mulInlineModify(ys, ntt);
  ASSERT_EQ(7, xs.size());
  EXPECT_EQ(3263884, xs[0]._v);
  EXPECT_EQ(7008180, xs[1]._v);
  EXPECT_EQ(4393991, xs[2]._v);
  EXPECT_EQ(4045475, xs[3]._v);
  EXPECT_EQ(4368242, xs[4]._v);
  EXPECT_EQ(5719417, xs[5]._v);
  EXPECT_EQ(4629639, xs[6]._v);
}

} // namespace math
