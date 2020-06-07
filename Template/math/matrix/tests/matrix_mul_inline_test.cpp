#include "gtest/gtest.h"

#include "math/matrix/matrix_mul_inline.h"

namespace math {

TEST(MatrixMulInline, test) {
  Matrix<> a(2, 3);
  a.at(0, 0) = 2;
  a.at(0, 1) = 1;
  a.at(0, 2) = 4;
  a.at(1, 0) = 0;
  a.at(1, 1) = 1;
  a.at(1, 2) = 1;
  Matrix<> b(3, 4);
  b.at(0, 0) = 6;
  b.at(0, 1) = 3;
  b.at(0, 2) = -1;
  b.at(0, 3) = 0;
  b.at(1, 0) = 1;
  b.at(1, 1) = 1;
  b.at(1, 2) = 0;
  b.at(1, 3) = 4;
  b.at(2, 0) = -2;
  b.at(2, 1) = 5;
  b.at(2, 2) = 0;
  b.at(2, 3) = 2;
  Matrix<> c;
  matrixMulModInline(c, a, b, 1000000007);
  EXPECT_EQ(c.n(), 2);
  EXPECT_EQ(c.m(), 4);
  EXPECT_EQ(c.at(0, 0), 5);
  EXPECT_EQ(c.at(0, 1), 27);
  EXPECT_EQ(c.at(0, 2), 1000000005);
  EXPECT_EQ(c.at(0, 3), 12);
  EXPECT_EQ(c.at(1, 0), 1000000006);
  EXPECT_EQ(c.at(1, 1), 6);
  EXPECT_EQ(c.at(1, 2), 0);
  EXPECT_EQ(c.at(1, 3), 6);
}

} // namespace math
