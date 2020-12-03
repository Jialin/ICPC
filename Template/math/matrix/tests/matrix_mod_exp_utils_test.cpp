#include "gtest/gtest.h"

#include "math/matrix/matrix_mod_exp_utils.h"
#include "math/matrix/matrix_vector.h"

namespace math {

TEST(MatrixModExpUtils, fib) {
  MatrixVector<> base(2, 2);
  base._vs[0][0] = 0;
  base._vs[0][1] = 1;
  base._vs[1][0] = 1;
  base._vs[1][1] = 1;
  MatrixModExpUtils<MatrixVector<>> expUtils(base, 1000000007);
  MatrixVector<> res;

  expUtils.calc(res, 0);
  EXPECT_EQ(2, res._n);
  EXPECT_EQ(2, res._m);
  EXPECT_EQ(1, res._vs[0][0]);
  EXPECT_EQ(0, res._vs[0][1]);
  EXPECT_EQ(0, res._vs[1][0]);
  EXPECT_EQ(1, res._vs[1][1]);

  expUtils.calc(res, 1);
  EXPECT_EQ(2, res._n);
  EXPECT_EQ(2, res._m);
  EXPECT_EQ(0, res._vs[0][0]);
  EXPECT_EQ(1, res._vs[0][1]);
  EXPECT_EQ(1, res._vs[1][0]);
  EXPECT_EQ(1, res._vs[1][1]);

  expUtils.calc(res, 50);
  EXPECT_EQ(2, res._n);
  EXPECT_EQ(2, res._m);
  EXPECT_EQ(778742000, res._vs[0][0]);
  EXPECT_EQ(586268941, res._vs[0][1]);
  EXPECT_EQ(586268941, res._vs[1][0]);
  EXPECT_EQ(365010934, res._vs[1][1]);
}

} // namespace math
