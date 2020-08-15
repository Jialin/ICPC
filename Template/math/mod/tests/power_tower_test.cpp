#include "gtest/gtest.h"

#include "math/mod/power_tower.h"

namespace math {

TEST(PowerTowerTest, basic) {
  vector<int> phis{
      1000000000, 400000000, 160000000, 64000000, 25600000, 10240000};
  EXPECT_EQ(powerTower({1}, phis), 1);
  EXPECT_EQ(powerTower({1, 2, 2, 3, 3, 3}, phis), 1);
  EXPECT_EQ(powerTower({2}, phis), 2);
  EXPECT_EQ(powerTower({2, 2}, phis), 4);
  EXPECT_EQ(powerTower({2, 2, 3}, phis), 256);
  EXPECT_EQ(powerTower({3}, phis), 3);
  EXPECT_EQ(powerTower({3, 3}, phis), 27);
  EXPECT_EQ(powerTower({3, 3, 3}, phis), 597484987);
}

TEST(PowerTowerTest, large) {
  vector<int> phis{20, 8, 4, 2, 1};
  EXPECT_EQ(
      powerTower({283309209, 762285205, 750900274, 160512987, 390669628}, phis),
      9);
  EXPECT_EQ(powerTower({205259431}, phis), 11);
  EXPECT_EQ(powerTower({160512987, 390669628, 205259431}, phis), 1);
  EXPECT_EQ(powerTower({750900274, 160512987, 390669628, 205259431}, phis), 4);
  EXPECT_EQ(powerTower({384332600}, phis), 0);
  EXPECT_EQ(powerTower({750900274}, phis), 14);
  EXPECT_EQ(
      powerTower({384332600, 283309209, 762285205, 750900274, 160512987}, phis),
      0);
}

} // namespace math
