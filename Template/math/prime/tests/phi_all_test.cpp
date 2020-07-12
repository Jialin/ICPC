#include "gtest/gtest.h"

#include "math/prime/phi_all.h"

namespace math {

TEST(PhiAll, test) {
  PhiAll phi(1000000 + 1);
  EXPECT_EQ(phi.get(0), 0);
  EXPECT_EQ(phi.get(1), 1);
  EXPECT_EQ(phi.get(2), 1);
  EXPECT_EQ(phi.get(3), 2);
  EXPECT_EQ(phi.get(4), 2);
  EXPECT_EQ(phi.get(5), 4);
  EXPECT_EQ(phi.get(999999), 466560);
  EXPECT_EQ(phi.get(1000000), 400000);
}

} // namespace math
