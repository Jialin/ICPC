#include "gtest/gtest.h"

#include "math/mod/log_coprime.h"

namespace math {

TEST(LogModCoprimeTest, basic) {
  LogModCoPrime<> logMod(100003);
  bool exist;

  exist = false;
  EXPECT_EQ(logMod.calc(5, 33, 58, exist), 9);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(logMod.calc(3, 13, 17, exist), 4);
  EXPECT_TRUE(exist);

  exist = false;
  EXPECT_EQ(logMod.calc(3, 1, 17, exist), 0);
  EXPECT_TRUE(exist);

  exist = true;
  logMod.calc(2, 3, 7, exist);
  EXPECT_FALSE(exist);
}

} // namespace math
