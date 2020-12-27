#include "gtest/gtest.h"

#include "math/mod/add.h"

namespace math {

TEST(AddMod, test) {
  EXPECT_EQ(3, addMod(2, 1, 4));
  EXPECT_EQ(0, addMod(2, 2, 4));
  EXPECT_EQ(1, addMod(2, 3, 4));
  EXPECT_EQ(2, addMod(2, 4, 4));
  EXPECT_EQ(3, addMod(2, 5, 4));
}

} // namespace math
