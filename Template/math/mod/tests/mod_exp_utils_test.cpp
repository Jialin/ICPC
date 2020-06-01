#include "gtest/gtest.h"

#include <vector>

#include "math/mod/mod_exp_utils.h"

using namespace std;

namespace math {

TEST(ModExpUtils, test) {
  ModExpUtils<> meu(2, 5);
  EXPECT_EQ(meu.exp(0), 1);
  EXPECT_EQ(meu.exp(3), 3);
  EXPECT_EQ(meu.exp(2147483646), 4);
  EXPECT_EQ(meu.exp(5), 2);
  EXPECT_EQ(meu.exp(123), 3);

  meu.init(2, 13);
  EXPECT_EQ(meu.exp(2147483647), 11);
  EXPECT_EQ(meu.exp(5), 6);
  EXPECT_EQ(meu.exp(123), 8);

  meu.init(1463, 29478);
  EXPECT_EQ(meu.exp(1397372724), 27031);
  EXPECT_EQ(meu.exp(12345), 3809);
}

TEST(ModExpUtils, testLargeBase) {
  ModExpUtils<> meu(7, 5);
  EXPECT_EQ(meu.exp(3), 3);
  EXPECT_EQ(meu.exp(2147483646), 4);
  EXPECT_EQ(meu.exp(5), 2);
  EXPECT_EQ(meu.exp(123), 3);
}

TEST(ExpModQuick, testMod1) {
  ModExpUtils<> meu(1, 1);
  EXPECT_EQ(meu.exp(0), 0);
  EXPECT_EQ(meu.exp(1), 0);

  meu.init(3, 1);
  EXPECT_EQ(meu.exp(2), 0);
}

} // namespace math
