#include "gtest/gtest.h"

#include "math/matrix/matrix_fix_inline.h"

namespace math {

TEST(MatrixFixInline, test) {
  Matrix<> a(3, 4);
  a.at(0, 0) = 6;
  a.at(0, 1) = 3;
  a.at(0, 2) = -1;
  a.at(0, 3) = 0;
  a.at(1, 0) = 1;
  a.at(1, 1) = 1;
  a.at(1, 2) = 0;
  a.at(1, 3) = 4;
  a.at(2, 0) = -2;
  a.at(2, 1) = 5;
  a.at(2, 2) = 0;
  a.at(2, 3) = 2;
  matrixFixModInline(a, 1000000007);
  EXPECT_EQ(a.n(), 3);
  EXPECT_EQ(a.m(), 4);
  EXPECT_EQ(a.at(0, 0), 6);
  EXPECT_EQ(a.at(0, 1), 3);
  EXPECT_EQ(a.at(0, 2), 1000000006);
  EXPECT_EQ(a.at(0, 3), 0);
  EXPECT_EQ(a.at(1, 0), 1);
  EXPECT_EQ(a.at(1, 1), 1);
  EXPECT_EQ(a.at(1, 2), 0);
  EXPECT_EQ(a.at(1, 3), 4);
  EXPECT_EQ(a.at(2, 0), 1000000005);
  EXPECT_EQ(a.at(2, 1), 5);
  EXPECT_EQ(a.at(2, 2), 0);
  EXPECT_EQ(a.at(2, 3), 2);
}

} // namespace math
