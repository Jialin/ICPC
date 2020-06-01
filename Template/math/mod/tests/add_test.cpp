#include "gtest/gtest.h"

#include "math/mod/add.h"

namespace math {

TEST(AddMod, test) {
  EXPECT_EQ(addMod(2, 1, 4), 3);
  EXPECT_EQ(addMod(2, 2, 4), 0);
  EXPECT_EQ(addMod(2, 3, 4), 1);
  EXPECT_EQ(addMod(2, 4, 4), 2);
  EXPECT_EQ(addMod(2, 5, 4), 3);
}

TEST(AddMod, testOverflow) {
  int32_t res = addMod<int32_t, int64_t>(2147483647, 2147483647, 1000000007);
  EXPECT_EQ(res, 294967266);
}

} // namespace math
