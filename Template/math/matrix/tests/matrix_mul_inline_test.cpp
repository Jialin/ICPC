#include "gtest/gtest.h"

#include "math/matrix/matrix_mul_inline.h"
#include "math/matrix/matrix_vector.h"

namespace math {

TEST(MatrixMulInline, test) {
  MatrixVector<> a(2, 3);
  a._vs[0][0] = 2;
  a._vs[0][1] = 1;
  a._vs[0][2] = 4;
  a._vs[1][0] = 0;
  a._vs[1][1] = 1;
  a._vs[1][2] = 1;
  MatrixVector<> b(3, 4);
  b._vs[0][0] = 6;
  b._vs[0][1] = 3;
  b._vs[0][2] = -1;
  b._vs[0][3] = 0;
  b._vs[1][0] = 1;
  b._vs[1][1] = 1;
  b._vs[1][2] = 0;
  b._vs[1][3] = 4;
  b._vs[2][0] = -2;
  b._vs[2][1] = 5;
  b._vs[2][2] = 0;
  b._vs[2][3] = 2;
  MatrixVector<> c;
  matrixMulModInline(c, a, b, 1000000007);
  EXPECT_EQ(2, c._n);
  EXPECT_EQ(4, c._m);
  EXPECT_EQ(5, c._vs[0][0]);
  EXPECT_EQ(27, c._vs[0][1]);
  EXPECT_EQ(1000000005, c._vs[0][2]);
  EXPECT_EQ(12, c._vs[0][3]);
  EXPECT_EQ(1000000006, c._vs[1][0]);
  EXPECT_EQ(6, c._vs[1][1]);
  EXPECT_EQ(0, c._vs[1][2]);
  EXPECT_EQ(6, c._vs[1][3]);
}

} // namespace math
