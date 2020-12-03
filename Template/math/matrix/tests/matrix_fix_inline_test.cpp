#include "gtest/gtest.h"

#include "math/matrix/matrix_fix_inline.h"
#include "math/matrix/matrix_vector.h"

namespace math {

TEST(MatrixFixInline, test) {
  MatrixVector<> a(3, 4);
  a._vs[0][0] = 6;
  a._vs[0][1] = 3;
  a._vs[0][2] = -1;
  a._vs[0][3] = 0;
  a._vs[1][0] = 1;
  a._vs[1][1] = 1;
  a._vs[1][2] = 0;
  a._vs[1][3] = 4;
  a._vs[2][0] = -2;
  a._vs[2][1] = 5;
  a._vs[2][2] = 0;
  a._vs[2][3] = 2;
  matrixFixModInline(a, 1000000007);
  EXPECT_EQ(3, a._n);
  EXPECT_EQ(4, a._m);
  EXPECT_EQ(6, a._vs[0][0]);
  EXPECT_EQ(3, a._vs[0][1]);
  EXPECT_EQ(1000000006, a._vs[0][2]);
  EXPECT_EQ(0, a._vs[0][3]);
  EXPECT_EQ(1, a._vs[1][0]);
  EXPECT_EQ(1, a._vs[1][1]);
  EXPECT_EQ(0, a._vs[1][2]);
  EXPECT_EQ(4, a._vs[1][3]);
  EXPECT_EQ(1000000005, a._vs[2][0]);
  EXPECT_EQ(5, a._vs[2][1]);
  EXPECT_EQ(0, a._vs[2][2]);
  EXPECT_EQ(2, a._vs[2][3]);
}

} // namespace math
