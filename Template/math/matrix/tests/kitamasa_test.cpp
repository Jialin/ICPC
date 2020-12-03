
#include "gtest/gtest.h"

#include "math/matrix/kitamasa.h"

namespace math {

TEST(Kitamasa, testOne) {
  Kitamasa<> kitamasa({2}, 1000000007);
  EXPECT_EQ(1, kitamasa.calc({1}, 0));
  EXPECT_EQ(2, kitamasa.calc({2}, 0));
  EXPECT_EQ(123, kitamasa.calc({123}, 0));

  EXPECT_EQ(2, kitamasa.calc({1}, 1));
  EXPECT_EQ(4, kitamasa.calc({1}, 2));
  EXPECT_EQ(8, kitamasa.calc({1}, 3));
  EXPECT_EQ(16, kitamasa.calc({1}, 4));
  EXPECT_EQ(32, kitamasa.calc({1}, 5));
  EXPECT_EQ(976371285, kitamasa.calc({1}, 100));

  for (auto& pow : kitamasa._pows)
    DEBUGV(pow);
}

TEST(Kitamasa, testFib) {
  Kitamasa<> kitamasa({1, 1}, 1000000007);
  EXPECT_EQ(1, kitamasa.calc({1, 0}, 0));
  EXPECT_EQ(0, kitamasa.calc({0, 1}, 0));
  EXPECT_EQ(0, kitamasa.calc({1, 0}, 1));
  EXPECT_EQ(1, kitamasa.calc({0, 1}, 1));

  EXPECT_EQ(0, kitamasa.calc({0, 1}, 0));
  EXPECT_EQ(1, kitamasa.calc({0, 1}, 1));
  EXPECT_EQ(1, kitamasa.calc({0, 1}, 2));
  EXPECT_EQ(2, kitamasa.calc({0, 1}, 3));
  EXPECT_EQ(3, kitamasa.calc({0, 1}, 4));
  EXPECT_EQ(5, kitamasa.calc({0, 1}, 5));
  EXPECT_EQ(8, kitamasa.calc({0, 1}, 6));
  EXPECT_EQ(13, kitamasa.calc({0, 1}, 7));
  EXPECT_EQ(832040, kitamasa.calc({0, 1}, 30));
  EXPECT_EQ(1346269, kitamasa.calc({0, 1}, 31));
  EXPECT_EQ(701408733, kitamasa.calc({0, 1}, 44));
  EXPECT_EQ(134903163, kitamasa.calc({0, 1}, 45));
  EXPECT_EQ(778742000, kitamasa.calc({0, 1}, 49));
  EXPECT_EQ(586268941, kitamasa.calc({0, 1}, 50));
  EXPECT_EQ(365010934, kitamasa.calc({0, 1}, 51));
  EXPECT_EQ(8745084, kitamasa.calc({0, 1}, 60));
  EXPECT_EQ(730764433, kitamasa.calc({0, 1}, 61));
  EXPECT_EQ(739509517, kitamasa.calc({0, 1}, 62));
}

} // namespace math