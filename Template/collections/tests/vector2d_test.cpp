#include "gtest/gtest.h"

#include "collections/vector2d.h"

namespace collections {

TEST(Vector2DTest, basic) {
  Vector2D<int> vs(3);
  EXPECT_EQ(vs._edgeIdx, 0);
  EXPECT_EQ(vs.lastOut[0], -1);
  EXPECT_EQ(vs.lastOut[1], -1);
  EXPECT_EQ(vs.lastOut[2], -1);

  vs.add(0, 10);
  vs.add(2, 20);
  EXPECT_EQ(vs._edgeIdx, 2);
  EXPECT_EQ(vs.values[0], 10);
  EXPECT_EQ(vs.values[1], 20);
  EXPECT_EQ(vs.nxtOut[0], -1);
  EXPECT_EQ(vs.nxtOut[1], -1);
  EXPECT_EQ(vs.lastOut[0], 0);
  EXPECT_EQ(vs.lastOut[1], -1);
  EXPECT_EQ(vs.lastOut[2], 1);

  vs.add(0, 30);
  vs.add(1, 40);
  EXPECT_EQ(vs._edgeIdx, 4);
  EXPECT_EQ(vs.values[0], 10);
  EXPECT_EQ(vs.values[1], 20);
  EXPECT_EQ(vs.values[2], 30);
  EXPECT_EQ(vs.values[3], 40);
  EXPECT_EQ(vs.nxtOut[0], -1);
  EXPECT_EQ(vs.nxtOut[1], -1);
  EXPECT_EQ(vs.nxtOut[2], 0);
  EXPECT_EQ(vs.nxtOut[3], -1);
  EXPECT_EQ(vs.lastOut[0], 2);
  EXPECT_EQ(vs.lastOut[1], 3);
  EXPECT_EQ(vs.lastOut[2], 1);
}

} // namespace collections
