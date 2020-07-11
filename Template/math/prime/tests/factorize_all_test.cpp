#include "gtest/gtest.h"

#include "math/prime/factorize_all.h"

namespace math {

TEST(FactorizeAll, test) {
  FactorizeAll fa(1024 + 1);
  vector<int> ps;
  vector<int> es;
  const auto& processor = [&ps, &es](int p, int e) {
    ps.push_back(p);
    es.push_back(e);
    return true;
  };

  fa.factorize(2, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);

  ps.clear();
  es.clear();
  fa.factorize(1024, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 10);

  ps.clear();
  es.clear();
  fa.factorize(10, processor);
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(es.size(), 2);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);
  EXPECT_EQ(ps[1], 5);
  EXPECT_EQ(es[1], 1);

  ps.clear();
  es.clear();
  fa.factorize(27, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 3);
  EXPECT_EQ(es[0], 3);

  ps.clear();
  es.clear();
  fa.factorize(840, processor);
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
  fa.factorize(1009, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 1009);
  EXPECT_EQ(es[0], 1);
}

} // namespace math
