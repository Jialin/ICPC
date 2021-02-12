#include "gtest/gtest.h"

#define FORWARD_STAR_EDGE_WEIGHTED_ALL
#include "graph/forward_star/forward_star_edge_weighted_macros.h"

#include "graph/forward_star/forward_star_edge_weighted.h"

namespace graph {

TEST(ForwardStarEdgeWeightedTest, basic) {
  ForwardStarEdgeWeighted<int> fs(3);
  ASSERT_EQ(fs._edgeIdx, 0);
  EXPECT_EQ(fs.lastOut[0], -1);
  EXPECT_EQ(fs.lastOut[1], -1);
  EXPECT_EQ(fs.lastOut[2], -1);

  fs.addDirected(0, 1, 10);
  fs.addDirected(1, 2, 20);
  ASSERT_EQ(fs._edgeIdx, 2);
  EXPECT_EQ(fs.nxtOut[0], -1);
  EXPECT_EQ(fs.nxtOut[1], -1);
  EXPECT_EQ(fs.weights[0], 10);
  EXPECT_EQ(fs.weights[1], 20);
  EXPECT_EQ(fs.toIdx[0], 1);
  EXPECT_EQ(fs.toIdx[1], 2);
  EXPECT_EQ(fs.lastOut[0], 0);
  EXPECT_EQ(fs.lastOut[1], 1);
  EXPECT_EQ(fs.lastOut[2], -1);

  fs.addUndirected(0, 2, 30);
  ASSERT_EQ(fs._edgeIdx, 4);
  EXPECT_EQ(fs.nxtOut[0], -1);
  EXPECT_EQ(fs.nxtOut[1], -1);
  EXPECT_EQ(fs.nxtOut[2], 0);
  EXPECT_EQ(fs.nxtOut[3], -1);
  EXPECT_EQ(fs.weights[0], 10);
  EXPECT_EQ(fs.weights[1], 20);
  EXPECT_EQ(fs.weights[2], 30);
  EXPECT_EQ(fs.weights[3], 30);
  EXPECT_EQ(fs.toIdx[0], 1);
  EXPECT_EQ(fs.toIdx[1], 2);
  EXPECT_EQ(fs.toIdx[2], 2);
  EXPECT_EQ(fs.toIdx[3], 0);
  EXPECT_EQ(fs.lastOut[0], 2);
  EXPECT_EQ(fs.lastOut[1], 1);
  EXPECT_EQ(fs.lastOut[2], 3);
}

} // namespace graph
