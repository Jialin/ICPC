#include "gtest/gtest.h"

#define BASE_RMQ_ALL
#include "ds/rmq/base_rmq_macros.h"

#include "ds/rmq/min_rmq.h"

namespace ds {

TEST(MinRMQTest, basic) {
  MinRMQ<int> rmq;
  rmq.init({3, 2, 1, 4, 5});
  int res;

  rmq.calc(0, 1, res);
  EXPECT_EQ(3, res);
  rmq.calc(1, 2, res);
  EXPECT_EQ(2, res);
  rmq.calc(2, 3, res);
  EXPECT_EQ(1, res);
  rmq.calc(3, 4, res);
  EXPECT_EQ(4, res);
  rmq.calc(4, 5, res);
  EXPECT_EQ(5, res);

  rmq.calc(0, 2, res);
  EXPECT_EQ(2, res);
  rmq.calc(1, 3, res);
  EXPECT_EQ(1, res);
  rmq.calc(2, 4, res);
  EXPECT_EQ(1, res);
  rmq.calc(3, 5, res);
  EXPECT_EQ(4, res);

  rmq.calc(0, 3, res);
  EXPECT_EQ(1, res);
  rmq.calc(1, 4, res);
  EXPECT_EQ(1, res);
  rmq.calc(2, 5, res);
  EXPECT_EQ(1, res);

  rmq.calc(0, 4, res);
  EXPECT_EQ(1, res);
  rmq.calc(1, 5, res);
  EXPECT_EQ(1, res);

  rmq.calc(0, 5, res);
  EXPECT_EQ(1, res);
}

} // namespace ds
