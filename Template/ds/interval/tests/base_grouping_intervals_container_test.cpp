#include "gtest/gtest.h"

#include "ds/interval/base_grouping_intervals_container.h"

namespace ds {

TEST(BaseGroupingIntervalsContainer, basic) {
  BaseGroupingIntervalsContainer<int, int> intervals;

  intervals.emplace(0, 3, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  auto it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second.upper);
  EXPECT_EQ(10, it->second.id);

  intervals.emplace(3, 6, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(6, it->second.upper);
  EXPECT_EQ(10, it->second.id);

  intervals.emplace(6, 9, 20);
  EXPECT_EQ(2, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(6, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(6, it->first);
  EXPECT_EQ(9, it->second.upper);
  EXPECT_EQ(20, it->second.id);

  intervals.emplace(3, 5, 30);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(3, it->first);
  EXPECT_EQ(5, it->second.upper);
  EXPECT_EQ(30, it->second.id);
  ++it;
  EXPECT_EQ(5, it->first);
  EXPECT_EQ(6, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(6, it->first);
  EXPECT_EQ(9, it->second.upper);
  EXPECT_EQ(20, it->second.id);

  intervals.emplace(4, 7, 40);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(3, it->first);
  EXPECT_EQ(4, it->second.upper);
  EXPECT_EQ(30, it->second.id);
  ++it;
  EXPECT_EQ(4, it->first);
  EXPECT_EQ(7, it->second.upper);
  EXPECT_EQ(40, it->second.id);
  ++it;
  EXPECT_EQ(7, it->first);
  EXPECT_EQ(9, it->second.upper);
  EXPECT_EQ(20, it->second.id);

  intervals.emplace(4, 7, 50);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(3, it->first);
  EXPECT_EQ(4, it->second.upper);
  EXPECT_EQ(30, it->second.id);
  ++it;
  EXPECT_EQ(4, it->first);
  EXPECT_EQ(7, it->second.upper);
  EXPECT_EQ(50, it->second.id);
  ++it;
  EXPECT_EQ(7, it->first);
  EXPECT_EQ(9, it->second.upper);
  EXPECT_EQ(20, it->second.id);

  intervals.emplace(9, 10, 10);
  EXPECT_EQ(5, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second.upper);
  EXPECT_EQ(10, it->second.id);
  ++it;
  EXPECT_EQ(3, it->first);
  EXPECT_EQ(4, it->second.upper);
  EXPECT_EQ(30, it->second.id);
  ++it;
  EXPECT_EQ(4, it->first);
  EXPECT_EQ(7, it->second.upper);
  EXPECT_EQ(50, it->second.id);
  ++it;
  EXPECT_EQ(7, it->first);
  EXPECT_EQ(9, it->second.upper);
  EXPECT_EQ(20, it->second.id);
  ++it;
  EXPECT_EQ(9, it->first);
  EXPECT_EQ(10, it->second.upper);
  EXPECT_EQ(10, it->second.id);

  intervals.emplace(2, 9, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(10, it->second.upper);
  EXPECT_EQ(10, it->second.id);
}

} // namespace ds
