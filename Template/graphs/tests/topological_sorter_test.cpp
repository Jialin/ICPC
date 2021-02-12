#include "gtest/gtest.h"

#define FORWARD_STAR_ALL
#include "graphs/forward_star/forward_star_macros.h"

#include "graphs/forward_star/forward_star.h"
#include "graphs/topological_sorter.h"

namespace graph {

TEST(TopologicalSorterTest, unconnected) {
  TopologicalSorter ts;
  vector<int> orders;
  auto processor = [&orders](int u) {
    orders.push_back(u);
  };
  ForwardStar fs(5);
  EXPECT_TRUE(ts.calc(fs, processor));

  EXPECT_EQ(orders.size(), 5);
  EXPECT_EQ(orders[0], 4);
  EXPECT_EQ(orders[1], 3);
  EXPECT_EQ(orders[2], 2);
  EXPECT_EQ(orders[3], 1);
  EXPECT_EQ(orders[4], 0);
}

TEST(TopologicalSorterTest, dag) {
  TopologicalSorter ts;
  vector<int> orders;
  auto processor = [&orders](int u) {
    orders.push_back(u);
  };
  ForwardStar fs(5);
  fs.addDirected(0, 1);
  fs.addDirected(0, 2);
  fs.addDirected(0, 3);
  fs.addDirected(1, 2);
  fs.addDirected(2, 3);
  fs.addDirected(2, 4);
  EXPECT_TRUE(ts.calc(fs, processor));

  EXPECT_EQ(orders.size(), 5);
  EXPECT_EQ(orders[0], 0);
  EXPECT_EQ(orders[1], 1);
  EXPECT_EQ(orders[2], 2);
  EXPECT_EQ(orders[3], 4);
  EXPECT_EQ(orders[4], 3);
}

TEST(TopologicalSorterTest, cyclic) {
  TopologicalSorter ts;
  vector<int> orders;
  auto processor = [&orders](int u) {
    orders.push_back(u);
  };
  ForwardStar fs(5);
  fs.addDirected(0, 1);
  fs.addDirected(0, 2);
  fs.addDirected(0, 3);
  fs.addDirected(1, 2);
  fs.addDirected(2, 3);
  fs.addUndirected(3, 4);

  EXPECT_FALSE(ts.calc(fs, processor));
  EXPECT_EQ(orders.size(), 3);
  EXPECT_EQ(orders[0], 0);
  EXPECT_EQ(orders[1], 1);
  EXPECT_EQ(orders[2], 2);
}

} // namespace graph
