#include "gtest/gtest.h"

#include "math/matrix/matrix_mod_exp_utils.h"

namespace math {

TEST(MatrixModExpUtils, testFib) {
  Matrix<> base(2, 2);
  base.at(0, 0) = 0;
  base.at(0, 1) = 1;
  base.at(1, 0) = 1;
  base.at(1, 1) = 1;
  MatrixModExpUtils<> expUtils(base, 1000000007);
  Matrix<> res;

  expUtils.exp(res, 0);
  EXPECT_EQ(res.n(), 2);
  EXPECT_EQ(res.m(), 2);
  EXPECT_EQ(res.at(0, 0), 1);
  EXPECT_EQ(res.at(0, 1), 0);
  EXPECT_EQ(res.at(1, 0), 0);
  EXPECT_EQ(res.at(1, 1), 1);

  expUtils.exp(res, 1);
  EXPECT_EQ(res.n(), 2);
  EXPECT_EQ(res.m(), 2);
  EXPECT_EQ(res.at(0, 0), 0);
  EXPECT_EQ(res.at(0, 1), 1);
  EXPECT_EQ(res.at(1, 0), 1);
  EXPECT_EQ(res.at(1, 1), 1);

  expUtils.exp(res, 50);
  EXPECT_EQ(res.n(), 2);
  EXPECT_EQ(res.m(), 2);
  EXPECT_EQ(res.at(0, 0), 778742000);
  EXPECT_EQ(res.at(0, 1), 586268941);
  EXPECT_EQ(res.at(1, 0), 586268941);
  EXPECT_EQ(res.at(1, 1), 365010934);
}

} // namespace math
