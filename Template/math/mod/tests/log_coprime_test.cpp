#include "gtest/gtest.h"

#include "math/mod/log_coprime.h"

namespace math {

TEST(LogModCoprimeTest, basic) {
  LogModCoPrime<> logMod(100003);
  int res;

  EXPECT_TRUE(logMod.calc(5, 33, 58, res));
  EXPECT_EQ(res, 9);

  EXPECT_TRUE(logMod.calc(3, 13, 17, res));
  EXPECT_EQ(res, 4);

  EXPECT_TRUE(logMod.calc(3, 1, 17, res));
  EXPECT_EQ(res, 0);

  EXPECT_FALSE(logMod.calc(2, 3, 7, res));
}

} // namespace math
