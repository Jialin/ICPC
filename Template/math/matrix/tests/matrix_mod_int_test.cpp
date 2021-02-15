#include "gtest/gtest.h"

#define MATRIX_MOD_INT_ALL
#include "math/matrix/matrix_mod_int_macros.h"

#include "math/matrix/matrix_mod_int.h"

namespace math {

TEST(MatrixModIntTest, solveModify) {
  const int MOD = 1000000007;
  MatrixModInt<int, int64_t, MOD> m;
  vector<ModInt<int, int64_t, MOD>> b, res;

  m.init(2, 2);
  m[0][0] = 0;
  m[0][1] = MOD - 1;
  m[1][0] = 1;
  m[1][1] = 2;
  b.assign(2, 0);
  b[0] = 1;
  m.solveModify(b, res);
  ASSERT_EQ(2, res.size());
  EXPECT_EQ(2, res[0]._v);
  EXPECT_EQ(MOD - 1, res[1]._v);

  m.init(3, 3);
  m[0][0] = 2;
  m[0][1] = 0;
  m[0][2] = 0;
  m[1][0] = 0;
  m[1][1] = 3;
  m[1][2] = 0;
  m[2][0] = 0;
  m[2][1] = 0;
  m[2][2] = 4;
  b.assign(3, 0);
  b[0] = 10;
  b[1] = 18;
  b[2] = 16;
  m.solveModify(b, res);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(5, res[0]._v);
  EXPECT_EQ(6, res[1]._v);
  EXPECT_EQ(4, res[2]._v);

  m.init(3, 3);
  m[0][0] = 0;
  m[0][1] = 3;
  m[0][2] = 0;
  m[1][0] = 0;
  m[1][1] = 0;
  m[1][2] = 4;
  m[2][0] = 2;
  m[2][1] = 0;
  m[2][2] = 0;
  b.assign(3, 0);
  b[0] = 18;
  b[1] = 16;
  b[2] = 10;
  m.solveModify(b, res);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(5, res[0]._v);
  EXPECT_EQ(6, res[1]._v);
  EXPECT_EQ(4, res[2]._v);

  m.init(3, 3);
  m[0][0] = 296640002;
  m[0][1] = 855637510;
  m[0][2] = 112233739;
  m[1][0] = 536320004;
  m[1][1] = 723735557;
  m[1][2] = 829721483;
  m[2][0] = 994880007;
  m[2][1] = 270944770;
  m[2][2] = 410558385;
  b.assign(3, 0);
  b[0] = 1;
  b[1] = 0;
  b[2] = 0;
  m.solveModify(b, res);
  ASSERT_EQ(3, res.size());
  EXPECT_EQ(745459206, res[0]._v);
  EXPECT_EQ(618185706, res[1]._v);
  EXPECT_EQ(818169493, res[2]._v);
}

} // namespace math
