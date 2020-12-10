#include "gtest/gtest.h"

#include "math/kitamasa/kitamasa_and_xor.h"

namespace math {

TEST(KitamasaAndXor, atcoder_abc009_d) {
  KitamasaAndXor<> ki;
  EXPECT_EQ(10, ki.calc({13, 19, 7}, {10, 20, 30}, 0));
  EXPECT_EQ(20, ki.calc({13, 19, 7}, {10, 20, 30}, 1));
  EXPECT_EQ(30, ki.calc({13, 19, 7}, {10, 20, 30}, 2));
  EXPECT_EQ(30, ki.calc({13, 19, 7}, {10, 20, 30}, 3));
  EXPECT_EQ(16, ki.calc({13, 19, 7}, {10, 20, 30}, 4));

  EXPECT_EQ(
      1067078691,
      ki.calc(
          {3434343434, 4294967294, 4294967295, 2147483647, 2147483648},
          {2345678901, 1001001001, 3333333333, 3141592653, 1234567890},
          99));
  EXPECT_EQ(
      2148,
      ki.calc(
          {544,  3437,  9981, 9319, 7077, 3307,  1415, 9746,  10882, 3649,
           1070, 11660, 2356, 9878, 786,  11136, 8162, 11594, 3046,  7638,
           2396, 12191, 150,  3628, 6961, 11241, 5032, 3271,  3613,  114},
          {11627, 5078, 8394,  6412,  10346, 3086, 3933, 668,  9879, 11739,
           4501,  6108, 12336, 8771,  2768,  2438, 2153, 7047, 5476, 313,
           1264,  369,  12070, 10743, 10663, 747,  370,  4671, 5235, 3439},
          999999998));
}

} // namespace math