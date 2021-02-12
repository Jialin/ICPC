#include "gtest/gtest.h"

#define FORWARD_STAR_ALL
#include "graphs/forward_star/forward_star_macros.h"

#include "graphs/forward_star/forward_star.h"

namespace graph {

TEST(ForwardStarTest, basic) {
  ForwardStar fs(3);
  EXPECT_EQ(fs._edgeIdx, 0);
  EXPECT_EQ(fs.lastOut[0], -1);
  EXPECT_EQ(fs.lastOut[1], -1);
  EXPECT_EQ(fs.lastOut[2], -1);
  EXPECT_EQ(fs.inDegree[0], 0);
  EXPECT_EQ(fs.inDegree[1], 0);
  EXPECT_EQ(fs.inDegree[2], 0);

  fs.addDirected(0, 1);
  fs.addDirected(1, 2);
  EXPECT_EQ(fs._edgeIdx, 2);
  EXPECT_EQ(fs.nxtOut[0], -1);
  EXPECT_EQ(fs.nxtOut[1], -1);
  EXPECT_EQ(fs.toIdx[0], 1);
  EXPECT_EQ(fs.toIdx[1], 2);
  EXPECT_EQ(fs.lastOut[0], 0);
  EXPECT_EQ(fs.lastOut[1], 1);
  EXPECT_EQ(fs.lastOut[2], -1);
  EXPECT_EQ(fs.inDegree[0], 0);
  EXPECT_EQ(fs.inDegree[1], 1);
  EXPECT_EQ(fs.inDegree[2], 1);

  fs.addUndirected(0, 2);
  EXPECT_EQ(fs._edgeIdx, 4);
  EXPECT_EQ(fs.nxtOut[0], -1);
  EXPECT_EQ(fs.nxtOut[1], -1);
  EXPECT_EQ(fs.nxtOut[2], 0);
  EXPECT_EQ(fs.nxtOut[3], -1);
  EXPECT_EQ(fs.toIdx[0], 1);
  EXPECT_EQ(fs.toIdx[1], 2);
  EXPECT_EQ(fs.toIdx[2], 2);
  EXPECT_EQ(fs.toIdx[3], 0);
  EXPECT_EQ(fs.lastOut[0], 2);
  EXPECT_EQ(fs.lastOut[1], 1);
  EXPECT_EQ(fs.lastOut[2], 3);
  EXPECT_EQ(fs.inDegree[0], 1);
  EXPECT_EQ(fs.inDegree[1], 1);
  EXPECT_EQ(fs.inDegree[2], 2);
}

} // namespace graph
