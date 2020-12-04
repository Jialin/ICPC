#include "gtest/gtest.h"

#include "math/gray_code.h"

namespace math {

TEST(GrayCode, test) {
  EXPECT_EQ(0, grayCode(0));
  EXPECT_EQ(1, grayCode(1));
  EXPECT_EQ(3, grayCode(2));
  EXPECT_EQ(2, grayCode(3));
  EXPECT_EQ(6, grayCode(4));
  EXPECT_EQ(7, grayCode(5));
  EXPECT_EQ(5, grayCode(6));
  EXPECT_EQ(4, grayCode(7));
}

} // namespace math
