#include "gtest/gtest.h"

#include "collections/unique_counter.h"

namespace collections {

TEST(UniqueCounterTest, basic) {
  UniqueCounter counter(10);

  EXPECT_EQ(counter.zeroCnt, 10);
  EXPECT_EQ(counter.nonZeroCnt, 0);

  counter.update(0, 1);
  counter.update(1, 1);
  counter.update(2, 1);
  counter.update(3, 1);
  EXPECT_EQ(counter.zeroCnt, 6);
  EXPECT_EQ(counter.nonZeroCnt, 4);

  counter.update(2, 1);
  counter.update(3, 1);
  counter.update(4, 1);
  counter.update(5, 1);
  EXPECT_EQ(counter.zeroCnt, 4);
  EXPECT_EQ(counter.nonZeroCnt, 6);

  counter.update(1, -1);
  counter.update(2, -1);
  EXPECT_EQ(counter.zeroCnt, 5);
  EXPECT_EQ(counter.nonZeroCnt, 5);
}

} // namespace collections
