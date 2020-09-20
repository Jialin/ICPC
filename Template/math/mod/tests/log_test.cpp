#include "gtest/gtest.h"

#include "math/mod/log.h"

namespace math {

TEST(LogModTest, exist) {
  LogMod<> logMod(100003);
  bool exist;

  EXPECT_EQ(logMod.calc(5, 33, 58, exist), 9);
  EXPECT_TRUE(exist);

  EXPECT_EQ(logMod.calc(3, 13, 17, exist), 4);
  EXPECT_TRUE(exist);

  EXPECT_EQ(logMod.calc(3, 1, 17, exist), 0);
  EXPECT_TRUE(exist);

  EXPECT_EQ(logMod.calc(6, 36, 218, exist), 2);
  EXPECT_TRUE(exist);
}

TEST(LogModTest, notExist) {
  LogMod<> logMod(100003);
  bool exist;

  exist = true;
  logMod.calc(2, 3, 4, exist);
  EXPECT_FALSE(exist);

  exist = true;
  logMod.calc(2, 3, 7, exist);
  EXPECT_FALSE(exist);
}

} // namespace math
