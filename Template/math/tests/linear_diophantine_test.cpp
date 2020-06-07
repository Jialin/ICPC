#include "gtest/gtest.h"

#include "math/linear_diophantine.h"

namespace math {

TEST(LinearDiophantine, test) {
  EXPECT_EQ(linearDiophantineSolutionCount(1, 1, 3, 0, 4, 0, 4), 4);
  EXPECT_EQ(linearDiophantineSolutionCount(1, -2, 29, -36, 23, -35, -4), 29);
  EXPECT_EQ(linearDiophantineSolutionCount(-2, 1, 50, -46, -28, -41, -39), 1);
  EXPECT_EQ(linearDiophantineSolutionCount(-1, -2, 34, -45, -21, -24, 31), 12);
  EXPECT_EQ(linearDiophantineSolutionCount(-2, -1, 33, -16, -9, -6, 37), 3);
  EXPECT_EQ(linearDiophantineSolutionCount(-2, -1, 21, 14, 24, 3, 16), 0);
  EXPECT_EQ(linearDiophantineSolutionCount(-2, -2, 48, -12, 10, -29, -27), 3);
  EXPECT_EQ(linearDiophantineSolutionCount(-1, -2, 47, -21, 39, 20, 31), 0);
  EXPECT_EQ(linearDiophantineSolutionCount(-1, 1, 36, 9, 12, -48, 14), 0);
  EXPECT_EQ(linearDiophantineSolutionCount(-2, -2, 20, -21, 30, -43, -10), 31);
  EXPECT_EQ(linearDiophantineSolutionCount(0, 0, 45, 22, 28, -5, 50), 0);
  EXPECT_EQ(linearDiophantineSolutionCount(-1, 0, -29, 11, 40, 16, 22), 7);
  EXPECT_EQ(linearDiophantineSolutionCount(-1, -2, 35, 18, 25, -41, 37), 4);
  EXPECT_EQ(linearDiophantineSolutionCount(0, 0, 0, 2, 4, 2, 5), 12);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          63125769, 40113320, 16531647, -56280824, 28391667, 8698147, 97138240),
      1);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          7554218,
          73321470,
          -31103534,
          -27761990,
          44636308,
          -70455302,
          43845195),
      2);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          24609000,
          47999742,
          -46028640,
          -83110292,
          60237765,
          -64566874,
          10862683),
      10);
  EXPECT_EQ(linearDiophantineSolutionCount(-6, 38, 642, 392, 411, 77, 98), 1);
  EXPECT_EQ(
      linearDiophantineSolutionCount(-74, -62, 380, -194, -148, 163, 220), 1);
  EXPECT_EQ(
      linearDiophantineSolutionCount(-21, 70, -665, 371, 392, 80, 117), 2);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          -896, 976, -47272032, 37875461, 37885074, 34720255, 34732090),
      158);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          -414, 92, -32907664, -6358268, -6344601, -28956763, -28948494),
      919);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          -283, 549, 3355322, 2995137, 3007335, 1542739, 1555837),
      20);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          791, -791, -1076551, -52031720, -52031711, -52030358, -52030352),
      7);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          -331, 993, 48990317, 39501481, 39507118, 13216521, 13222951),
      1855);
  EXPECT_EQ(
      linearDiophantineSolutionCount(955, -708, 911, -386, 167, -408, -92), 0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(886, 45, 235, -529, 343, 431, 627), 0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          12435967,
          -64554079,
          16697503,
          -63496641,
          -56348530,
          -70521600,
          12645700),
      0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          34509417,
          -16720808,
          50317024,
          -69987409,
          -3347569,
          -50198713,
          -30047779),
      0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          81927384, 21165094, 14400170, 14000463, 83415249, 42485596, 61541107),
      0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(
          -77678074,
          -63842029,
          -9017620,
          25459792,
          76760835,
          76097529,
          98283722),
      0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(0, 240, 513, 638, 743, -647, 911), 0);
  EXPECT_EQ(
      linearDiophantineSolutionCount(-264, 0, -712, -326, 540, -63, 800), 0);
  EXPECT_EQ(linearDiophantineSolutionCount(0, -14, -686, 88, 135, 44, 62), 48);
  EXPECT_EQ(
      linearDiophantineSolutionCount(0, 50, 1000, -300, -257, 11, 34), 44);
  EXPECT_EQ(
      linearDiophantineSolutionCount(0, 3, 9, -100000000, 100000000, 3, 3),
      200000001);
}

} // namespace math
