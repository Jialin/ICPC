#include "gtest/gtest.h"

#include "math/fib/fib_general.h"

namespace math {

TEST(FibGeneral, fib) {
  EXPECT_EQ(0, fibGeneral(0, 0, 1, 1000000007));
  EXPECT_EQ(1, fibGeneral(1, 0, 1, 1000000007));
  EXPECT_EQ(1, fibGeneral(2, 0, 1, 1000000007));
  EXPECT_EQ(2, fibGeneral(3, 0, 1, 1000000007));
  EXPECT_EQ(3, fibGeneral(4, 0, 1, 1000000007));
  EXPECT_EQ(832040, fibGeneral(30, 0, 1, 1000000007));
  EXPECT_EQ(1346269, fibGeneral(31, 0, 1, 1000000007));
  EXPECT_EQ(701408733, fibGeneral(44, 0, 1, 1000000007));
  EXPECT_EQ(134903163, fibGeneral(45, 0, 1, 1000000007));
  EXPECT_EQ(778742000, fibGeneral(49, 0, 1, 1000000007));
  EXPECT_EQ(586268941, fibGeneral(50, 0, 1, 1000000007));
}

TEST(FibGeneral, custom) {
  EXPECT_EQ(99, fibGeneral(0, 99, 100, 1000000007));
  EXPECT_EQ(100, fibGeneral(1, 99, 100, 1000000007));
  EXPECT_EQ(199, fibGeneral(2, 99, 100, 1000000007));
  EXPECT_EQ(299, fibGeneral(3, 99, 100, 1000000007));
  EXPECT_EQ(8866, fibGeneral(10, 99, 100, 1000000007));
  EXPECT_EQ(126199942, fibGeneral(100, 99, 100, 1000000007));
  EXPECT_EQ(5864968, fibGeneral(183813, 283, 3838, 1000000007));
}

} // namespace math
