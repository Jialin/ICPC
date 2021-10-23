#include "gtest/gtest.h"

#include <utility>

#define BASE_MIN_QUEUE_ALL
#include "ds/min_queue/base_min_queue_macros.h"

#include "ds/min_queue/max_queue.h"

using namespace std;

namespace ds {

TEST(MaxQueueTest, basic) {
  MaxQueue<pair<int, int>> mq;
  pair<int, int> res;

  mq.push_back({{4, 0}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(4, res.first);
  EXPECT_EQ(0, res.second);

  mq.push_back({{3, 1}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(4, res.first);
  EXPECT_EQ(0, res.second);

  mq.push_back({{5, 2}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(5, res.first);
  EXPECT_EQ(2, res.second);

  mq.pop_front();
  mq.push_back({{2, 3}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(5, res.first);
  EXPECT_EQ(2, res.second);

  mq.pop_front();
  mq.push_back({{1, 4}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(5, res.first);
  EXPECT_EQ(2, res.second);

  mq.pop_front();
  mq.push_back({{0, 5}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(2, res.first);
  EXPECT_EQ(3, res.second);

  mq.pop_front();
  mq.push_back({{2, 6}, {0, 0}});
  mq.calc(res);
  EXPECT_EQ(2, res.first);
  EXPECT_EQ(6, res.second);
}

} // namespace ds
