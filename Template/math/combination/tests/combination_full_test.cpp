#include "gtest/gtest.h"

#include "math/combination/combination_full.h"
#include "math/prime/prime_generator.h"

namespace math {

TEST(CombinationModFullTest, mod2) {
  PrimeGenerator pg(100);
  CombinationModFull<> comb(6, 2, pg.primes);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 0);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 1);
  EXPECT_EQ(comb.calc(3, 2), 1);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 0);
  EXPECT_EQ(comb.calc(4, 2), 0);
  EXPECT_EQ(comb.calc(4, 3), 0);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 1);
  EXPECT_EQ(comb.calc(5, 2), 0);
  EXPECT_EQ(comb.calc(5, 3), 0);
  EXPECT_EQ(comb.calc(5, 4), 1);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModFullTest, mod3) {
  PrimeGenerator pg(100);
  CombinationModFull<> comb(6, 3, pg.primes);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 0);
  EXPECT_EQ(comb.calc(3, 2), 0);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 1);
  EXPECT_EQ(comb.calc(4, 2), 0);
  EXPECT_EQ(comb.calc(4, 3), 1);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 2);
  EXPECT_EQ(comb.calc(5, 2), 1);
  EXPECT_EQ(comb.calc(5, 3), 1);
  EXPECT_EQ(comb.calc(5, 4), 2);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModFullTest, mod4) {
  PrimeGenerator pg(100);
  CombinationModFull<> comb(6, 4, pg.primes);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 3);
  EXPECT_EQ(comb.calc(3, 2), 3);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 0);
  EXPECT_EQ(comb.calc(4, 2), 2);
  EXPECT_EQ(comb.calc(4, 3), 0);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 1);
  EXPECT_EQ(comb.calc(5, 2), 2);
  EXPECT_EQ(comb.calc(5, 3), 2);
  EXPECT_EQ(comb.calc(5, 4), 1);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModFullTest, mod6) {
  PrimeGenerator pg(100);
  CombinationModFull<> comb(6, 6, pg.primes);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 3);
  EXPECT_EQ(comb.calc(3, 2), 3);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 4);
  EXPECT_EQ(comb.calc(4, 2), 0);
  EXPECT_EQ(comb.calc(4, 3), 4);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 5);
  EXPECT_EQ(comb.calc(5, 2), 4);
  EXPECT_EQ(comb.calc(5, 3), 4);
  EXPECT_EQ(comb.calc(5, 4), 5);
  EXPECT_EQ(comb.calc(5, 5), 1);
}

TEST(CombinationModFullTest, largePrime) {
  PrimeGenerator pg(100000);
  CombinationModFull<> comb(6, 100007, pg.primes);
  EXPECT_EQ(comb.calc(0, 0), 1);
  EXPECT_EQ(comb.calc(1, 1), 1);
  EXPECT_EQ(comb.calc(1, 2), 0);
  EXPECT_EQ(comb.calc(2, 0), 1);
  EXPECT_EQ(comb.calc(2, 1), 2);
  EXPECT_EQ(comb.calc(2, 2), 1);
  EXPECT_EQ(comb.calc(3, 0), 1);
  EXPECT_EQ(comb.calc(3, 1), 3);
  EXPECT_EQ(comb.calc(3, 2), 3);
  EXPECT_EQ(comb.calc(3, 3), 1);
  EXPECT_EQ(comb.calc(4, 0), 1);
  EXPECT_EQ(comb.calc(4, 1), 4);
  EXPECT_EQ(comb.calc(4, 2), 6);
  EXPECT_EQ(comb.calc(4, 3), 4);
  EXPECT_EQ(comb.calc(4, 4), 1);
  EXPECT_EQ(comb.calc(5, 0), 1);
  EXPECT_EQ(comb.calc(5, 1), 5);
  EXPECT_EQ(comb.calc(5, 2), 10);
  EXPECT_EQ(comb.calc(5, 3), 10);
  EXPECT_EQ(comb.calc(5, 4), 5);
  EXPECT_EQ(comb.calc(5, 5), 1);

  comb.init(100000, 1000000007, pg.primes);
  EXPECT_EQ(comb.calc(1231, 300), 296144006);
  EXPECT_EQ(comb.calc(99999, 44454), 750649176);
}

TEST(CombinationModFullTest, largeComposite) {
  PrimeGenerator pg(100000);
  CombinationModFull<> comb(100000, 3818213, pg.primes);
  EXPECT_EQ(comb.calc(1231, 300), 912415);
  EXPECT_EQ(comb.calc(99999, 44454), 707077);
  EXPECT_EQ(comb.calc(42311, 17371), 394219);

  CombinationModFull<int64_t> comb64(100000, 2147483647, pg.primes);
  EXPECT_EQ(comb64.calc(1231, 300), 1924759492);
  EXPECT_EQ(comb64.calc(99999, 44454), 255651975);

  comb64.init(100000, 2147483645, pg.primes);
  EXPECT_EQ(comb64.calc(1231, 300), 1461459556);
  EXPECT_EQ(comb64.calc(99999, 44454), 1836286920);
}

} // namespace math
