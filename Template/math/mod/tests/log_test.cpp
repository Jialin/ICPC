#include "gtest/gtest.h"

#include "math/mod/log.h"

namespace math {

TEST(LogModTest, basic) {
  LogMod<> logMod(100003);
  int res;

  EXPECT_TRUE(logMod.calc(5, 33, 58, res));
  EXPECT_EQ(res, 9);

  EXPECT_TRUE(logMod.calc(3, 13, 17, res));
  EXPECT_EQ(res, 4);

  EXPECT_TRUE(logMod.calc(3, 1, 17, res));
  EXPECT_EQ(res, 0);

  EXPECT_TRUE(logMod.calc(6, 36, 218, res));
  EXPECT_EQ(res, 2);

  EXPECT_FALSE(logMod.calc(2, 3, 4, res));
  EXPECT_FALSE(logMod.calc(2, 3, 7, res));
}

} // namespace math
