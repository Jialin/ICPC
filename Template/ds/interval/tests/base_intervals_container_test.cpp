#include "gtest/gtest.h"

#define BASE_INTERVALS_CONTAINER_ALL
#include "ds/interval/base_intervals_container_macros.h"

#include "ds/interval/base_intervals_container.h"

namespace ds {

TEST(BaseIntervalsContainer, emplace) {
  BaseIntervalsContainer<int> intervals;

  intervals.emplace(0, 3);
  EXPECT_EQ(1, intervals._intervals.size());
  auto it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second);

  intervals.emplace(3, 6);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(6, it->second);

  intervals.emplace(7, 9);
  EXPECT_EQ(2, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(6, it->second);
  ++it;
  EXPECT_EQ(7, it->first);
  EXPECT_EQ(9, it->second);

  intervals.emplace(6, 7);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(9, it->second);
}

TEST(BaseIntervalsContainer, erase) {
  BaseIntervalsContainer<int> intervals;

  intervals.emplace(0, 3);
  intervals.emplace(4, 7);
  intervals.emplace(8, 10);
  EXPECT_EQ(3, intervals._intervals.size());
  auto it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second);
  ++it;
  EXPECT_EQ(4, it->first);
  EXPECT_EQ(7, it->second);
  ++it;
  EXPECT_EQ(8, it->first);
  EXPECT_EQ(10, it->second);

  intervals.erase(5, 6);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(3, it->second);
  ++it;
  EXPECT_EQ(4, it->first);
  EXPECT_EQ(5, it->second);
  ++it;
  EXPECT_EQ(6, it->first);
  EXPECT_EQ(7, it->second);
  ++it;
  EXPECT_EQ(8, it->first);
  EXPECT_EQ(10, it->second);

  intervals.erase(2, 9);
  EXPECT_EQ(2, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->first);
  EXPECT_EQ(2, it->second);
  ++it;
  EXPECT_EQ(9, it->first);
  EXPECT_EQ(10, it->second);
}

} // namespace ds
