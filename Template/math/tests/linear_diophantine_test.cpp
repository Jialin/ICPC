#include "gtest/gtest.h"

#include "math/linear_diophantine.h"

namespace math {

TEST(LinearDiophantine, test) {
  EXPECT_EQ(linearDiophantineSolutionCount(1, 1, 3, 0, 4, 0, 4), 4);
}

} // namespace math
