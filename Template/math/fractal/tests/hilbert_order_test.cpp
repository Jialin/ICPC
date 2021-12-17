#include "gtest/gtest.h"

#include "math/fractal/hilbert_order.h"

namespace math {

TEST(HilbertOrder, basic) {
  EXPECT_EQ(0, hilbertOrder(0, 0, 0));

  EXPECT_EQ(0, hilbertOrder(1, 0, 0));
  EXPECT_EQ(3, hilbertOrder(1, 0, 1));
  EXPECT_EQ(1, hilbertOrder(1, 1, 0));
  EXPECT_EQ(2, hilbertOrder(1, 1, 1));

  EXPECT_EQ(0, hilbertOrder(2, 0, 0));
  EXPECT_EQ(1, hilbertOrder(2, 0, 1));
  EXPECT_EQ(14, hilbertOrder(2, 0, 2));
  EXPECT_EQ(15, hilbertOrder(2, 0, 3));
  EXPECT_EQ(3, hilbertOrder(2, 1, 0));
  EXPECT_EQ(2, hilbertOrder(2, 1, 1));
  EXPECT_EQ(13, hilbertOrder(2, 1, 2));
  EXPECT_EQ(12, hilbertOrder(2, 1, 3));
  EXPECT_EQ(4, hilbertOrder(2, 2, 0));
  EXPECT_EQ(7, hilbertOrder(2, 2, 1));
  EXPECT_EQ(8, hilbertOrder(2, 2, 2));
  EXPECT_EQ(11, hilbertOrder(2, 2, 3));
  EXPECT_EQ(5, hilbertOrder(2, 3, 0));
  EXPECT_EQ(6, hilbertOrder(2, 3, 1));
  EXPECT_EQ(9, hilbertOrder(2, 3, 2));
  EXPECT_EQ(10, hilbertOrder(2, 3, 3));

  EXPECT_EQ(3, hilbertOrder(3, 0, 1));
  EXPECT_EQ(7, hilbertOrder(3, 1, 2));
  EXPECT_EQ(9, hilbertOrder(3, 2, 3));
  EXPECT_EQ(53, hilbertOrder(3, 3, 4));
  EXPECT_EQ(33, hilbertOrder(3, 4, 5));
  EXPECT_EQ(45, hilbertOrder(3, 5, 6));
  EXPECT_EQ(43, hilbertOrder(3, 6, 7));
}

} // namespace math
