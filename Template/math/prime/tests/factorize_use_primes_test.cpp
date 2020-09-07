#include "gtest/gtest.h"

#include "math/prime/factorize_use_primes.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(FactorizeUsePrimesTest, basic) {
  PrimeGenerator pg(1024);
  vector<int> ps;
  vector<int> es;
  const auto& processor = [&ps, &es](int p, int e) {
    ps.push_back(p);
    es.push_back(e);
  };

  factorizeUsePrimes<int, int>(2, pg.primes, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);

  ps.clear();
  es.clear();
  factorizeUsePrimes<int, int>(1024, pg.primes, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 10);

  ps.clear();
  es.clear();
  factorizeUsePrimes<int, int>(10, pg.primes, processor);
  EXPECT_EQ(ps.size(), 2);
  EXPECT_EQ(es.size(), 2);
  EXPECT_EQ(ps[0], 2);
  EXPECT_EQ(es[0], 1);
  EXPECT_EQ(ps[1], 5);
  EXPECT_EQ(es[1], 1);

  ps.clear();
  es.clear();
  factorizeUsePrimes<int, int>(27, pg.primes, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 3);
  EXPECT_EQ(es[0], 3);

  ps.clear();
  es.clear();
  factorizeUsePrimes<int, int>(840, pg.primes, processor);
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
  factorizeUsePrimes<int, int>(1009, pg.primes, processor);
  EXPECT_EQ(ps.size(), 1);
  EXPECT_EQ(es.size(), 1);
  EXPECT_EQ(ps[0], 1009);
  EXPECT_EQ(es[0], 1);
}

} // namespace math
