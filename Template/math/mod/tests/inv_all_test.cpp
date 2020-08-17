#include "gtest/gtest.h"

#include "math/mod/inv_all.h"

namespace math {

TEST(InvModAllTest, small) {
  InvModAll invModAll(3, 3);
  EXPECT_EQ(invModAll.get(2), 2);

  invModAll.init(18, 101);
  EXPECT_EQ(invModAll.get(17), 6);
}

TEST(InvModAllTest, large) {
  InvModAll invModAll(12346, 1000000007);
  EXPECT_EQ(invModAll.get(12345), 203483193);
}

} // namespace math
