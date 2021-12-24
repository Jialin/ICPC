#include "gtest/gtest.h"

#include "ds/base_valued_interval_container.h"

namespace ds {

TEST(BaseValuedIntervalContainer, basic) {
  BaseValuedIntervalContainer<int, int> intervals;

  intervals.emplace(0, 3, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  auto it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->v);

  intervals.emplace(3, 6, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->v);

  intervals.emplace(6, 9, 20);
  EXPECT_EQ(2, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(6, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->v);

  intervals.emplace(3, 5, 30);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(5, it->upper);
  EXPECT_EQ(30, it->v);
  ++it;
  EXPECT_EQ(5, it->lower);
  EXPECT_EQ(6, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(6, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->v);

  intervals.emplace(4, 7, 40);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->v);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(40, it->v);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->v);

  intervals.emplace(4, 7, 50);
  EXPECT_EQ(4, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->v);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(50, it->v);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->v);

  intervals.emplace(9, 10, 10);
  EXPECT_EQ(5, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(3, it->upper);
  EXPECT_EQ(10, it->v);
  ++it;
  EXPECT_EQ(3, it->lower);
  EXPECT_EQ(4, it->upper);
  EXPECT_EQ(30, it->v);
  ++it;
  EXPECT_EQ(4, it->lower);
  EXPECT_EQ(7, it->upper);
  EXPECT_EQ(50, it->v);
  ++it;
  EXPECT_EQ(7, it->lower);
  EXPECT_EQ(9, it->upper);
  EXPECT_EQ(20, it->v);
  ++it;
  EXPECT_EQ(9, it->lower);
  EXPECT_EQ(10, it->upper);
  EXPECT_EQ(10, it->v);

  intervals.emplace(2, 9, 10);
  EXPECT_EQ(1, intervals._intervals.size());
  it = intervals._intervals.begin();
  EXPECT_EQ(0, it->lower);
  EXPECT_EQ(10, it->upper);
  EXPECT_EQ(10, it->v);
}

} // namespace ds
