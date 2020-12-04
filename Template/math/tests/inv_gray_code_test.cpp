#include "gtest/gtest.h"

#include "math/inv_gray_code.h"

namespace math {

TEST(InvGrayCode, test) {
  EXPECT_EQ(0, invGrayCode(0));
  EXPECT_EQ(1, invGrayCode(1));
  EXPECT_EQ(3, invGrayCode(2));
  EXPECT_EQ(2, invGrayCode(3));
  EXPECT_EQ(7, invGrayCode(4));
  EXPECT_EQ(6, invGrayCode(5));
  EXPECT_EQ(4, invGrayCode(6));
  EXPECT_EQ(5, invGrayCode(7));
}

} // namespace math
