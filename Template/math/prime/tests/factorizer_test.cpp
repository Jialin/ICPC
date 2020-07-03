#include "gtest/gtest.h"

#include "math/prime/factorizer.h"

namespace math {

TEST(Factorizer, test) {
  Factorizer f(1024 + 1);
  vector<int> ps;
  vector<int> es;
  const auto& processor = [&ps, &es](int p, int e) {
    ps.push_back(p);
    es.push_back(e);
    return true;
  };

  f.factorize(2, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);

  ps.clear();
  es.clear();
  f.factorize(1024, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 10);

  ps.clear();
  es.clear();
  f.factorize(10, processor);
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(es.size(), 2);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);
  EXPECT_EQ(ps[1], 5);
  EXPECT_EQ(es[1], 1);

  ps.clear();
  es.clear();
  f.factorize(27, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 3);
  EXPECT_EQ(es[0], 3);

  ps.clear();
  es.clear();
  f.factorize(840, processor);
  EXPECT_EQ(ps.size(), 4);
  EXPECT_EQ(es.size(), 4);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 3);
  EXPECT_EQ(ps[1], 3);
  EXPECT_EQ(es[1], 1);
  EXPECT_EQ(ps[2], 5);
  EXPECT_EQ(es[2], 1);
  EXPECT_EQ(ps[3], 7);
  EXPECT_EQ(es[3], 1);

  ps.clear();
  es.clear();
  f.factorize(1009, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 1009);
  EXPECT_EQ(es[0], 1);
}

} // namespace math
