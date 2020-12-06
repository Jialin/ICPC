#include "gtest/gtest.h"

#include "math/bit/submasks.h"

namespace math {

TEST(Submasks, basic) {
  vector<int> vs;
  submasks(7, [&vs](int v) { vs.emplace_back(v); });
  sort(vs.begin(), vs.end());
  ASSERT_EQ(8, vs.size());
  EXPECT_EQ(0, vs[0]);
  EXPECT_EQ(1, vs[1]);
  EXPECT_EQ(2, vs[2]);
  EXPECT_EQ(3, vs[3]);
  EXPECT_EQ(4, vs[4]);
  EXPECT_EQ(5, vs[5]);
  EXPECT_EQ(6, vs[6]);
  EXPECT_EQ(7, vs[7]);
}

TEST(Submasks, large) {
  vector<int> vs;
  submasks(262184, [&vs](int v) { vs.emplace_back(v); });
  sort(vs.begin(), vs.end());
  ASSERT_EQ(8, vs.size());
  EXPECT_EQ(0, vs[0]);
  EXPECT_EQ(8, vs[1]);
  EXPECT_EQ(32, vs[2]);
  EXPECT_EQ(40, vs[3]);
  EXPECT_EQ(262144, vs[4]);
  EXPECT_EQ(262152, vs[5]);
  EXPECT_EQ(262176, vs[6]);
  EXPECT_EQ(262184, vs[7]);
}

TEST(Submasks, zero) {
  vector<int> vs;
  submasks(0, [&vs](int v) { vs.emplace_back(v); });
  ASSERT_EQ(1, vs.size());
  EXPECT_EQ(0, vs[0]);
}

} // namespace math
