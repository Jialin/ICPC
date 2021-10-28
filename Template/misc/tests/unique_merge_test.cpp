#include "gtest/gtest.h"

#include "misc/unique_merge.h"

using namespace std;

namespace misc {

TEST(UniqueMergeTest, basic) {
  vector<pair<int, int>> vs{{1, 1}, {2, 3}, {1, 4}, {3, 5}, {4, 6}, {2, -2}};
  uniqueMerge(vs);
  EXPECT_EQ(1, vs[0].first);
  EXPECT_EQ(5, vs[0].second);
  EXPECT_EQ(2, vs[1].first);
  EXPECT_EQ(1, vs[1].second);
  EXPECT_EQ(3, vs[2].first);
  EXPECT_EQ(5, vs[2].second);
  EXPECT_EQ(4, vs[3].first);
  EXPECT_EQ(6, vs[3].second);
}

}
