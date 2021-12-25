#include "gtest/gtest.h"

#include "ds/interval/base_grouping_intervals_container.h"

namespace ds {

TEST(BaseGroupingIntervalsContainer, basic) {
  BaseGroupingIntervalsContainer<int, int> intervals;

  intervals.emplace(0, 3, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  auto it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->id);

  intervals.emplace(3, 6, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->id);

  intervals.emplace(6, 9, 20);
  EXPECT_EQ(2, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(6, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->id);

  intervals.emplace(3, 5, 30);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(5, it->upper);
  EXPECT_EQ(30, it->id);
  ++it;
  EXPECT_EQ(5, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(6, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->id);

  intervals.emplace(4, 7, 40);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->id);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(40, it->id);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->id);

  intervals.emplace(4, 7, 50);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->id);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(50, it->id);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->id);

  intervals.emplace(9, 10, 10);
  EXPECT_EQ(5, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->id);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->id);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(50, it->id);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->id);
  ++it;
  EXPECT_EQ(9, it->lower);
  EXPECT_EQ(10, it->upper);
  EXPECT_EQ(10, it->id);

  intervals.emplace(2, 9, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(10, it->upper);
  EXPECT_EQ(10, it->id);
}

} // namespace ds
