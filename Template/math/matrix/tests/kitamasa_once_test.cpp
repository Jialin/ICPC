
#include "gtest/gtest.h"

#include "math/matrix/kitamasa_once.h"

namespace math {

TEST(KitamasaOnce, one) {
  KitamasaOnce<> ki;
  EXPECT_EQ(1, ki.calc({2}, {1}, 0, 1000000007));
  EXPECT_EQ(2, ki.calc({2}, {2}, 0, 1000000007));
  EXPECT_EQ(123, ki.calc({2}, {123}, 0, 1000000007));

  EXPECT_EQ(2, ki.calc({2}, {1}, 1, 1000000007));
  EXPECT_EQ(4, ki.calc({2}, {1}, 2, 1000000007));
  EXPECT_EQ(8, ki.calc({2}, {1}, 3, 1000000007));
  EXPECT_EQ(16, ki.calc({2}, {1}, 4, 1000000007));
  EXPECT_EQ(32, ki.calc({2}, {1}, 5, 1000000007));
  EXPECT_EQ(976371285, ki.calc({2}, {1}, 100, 1000000007));
}

TEST(KitamasaOnce, fib) {
  KitamasaOnce<> ki;
  EXPECT_EQ(1, ki.calc({1, 1}, {1, 0}, 0, 1000000007));
  EXPECT_EQ(0, ki.calc({1, 1}, {0, 1}, 0, 1000000007));
  EXPECT_EQ(0, ki.calc({1, 1}, {1, 0}, 1, 1000000007));
  EXPECT_EQ(1, ki.calc({1, 1}, {0, 1}, 1, 1000000007));

  EXPECT_EQ(0, ki.calc({1, 1}, {0, 1}, 0, 1000000007));
  EXPECT_EQ(1, ki.calc({1, 1}, {0, 1}, 1, 1000000007));
  EXPECT_EQ(1, ki.calc({1, 1}, {0, 1}, 2, 1000000007));
  EXPECT_EQ(2, ki.calc({1, 1}, {0, 1}, 3, 1000000007));
  EXPECT_EQ(3, ki.calc({1, 1}, {0, 1}, 4, 1000000007));
  EXPECT_EQ(5, ki.calc({1, 1}, {0, 1}, 5, 1000000007));
  EXPECT_EQ(8, ki.calc({1, 1}, {0, 1}, 6, 1000000007));
  EXPECT_EQ(13, ki.calc({1, 1}, {0, 1}, 7, 1000000007));
  EXPECT_EQ(832040, ki.calc({1, 1}, {0, 1}, 30, 1000000007));
  EXPECT_EQ(1346269, ki.calc({1, 1}, {0, 1}, 31, 1000000007));
  EXPECT_EQ(701408733, ki.calc({1, 1}, {0, 1}, 44, 1000000007));
  EXPECT_EQ(134903163, ki.calc({1, 1}, {0, 1}, 45, 1000000007));
  EXPECT_EQ(778742000, ki.calc({1, 1}, {0, 1}, 49, 1000000007));
  EXPECT_EQ(586268941, ki.calc({1, 1}, {0, 1}, 50, 1000000007));
  EXPECT_EQ(365010934, ki.calc({1, 1}, {0, 1}, 51, 1000000007));
  EXPECT_EQ(8745084, ki.calc({1, 1}, {0, 1}, 60, 1000000007));
  EXPECT_EQ(730764433, ki.calc({1, 1}, {0, 1}, 61, 1000000007));
  EXPECT_EQ(739509517, ki.calc({1, 1}, {0, 1}, 62, 1000000007));
}

} // namespace math