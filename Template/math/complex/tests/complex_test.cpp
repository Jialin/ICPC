#include "gtest/gtest.h"

#define COMPLEX_ALL
#include "math/complex/complex_macros.h"

#include "math/complex/complex.h"

using namespace std;

namespace math {

TEST(Complex, mul) {
  Complex<double> x, y, res;

  x.init(3, 4);
  y.init(5, 6);
  res = x * y;
  EXPECT_EQ(-9, res.real);
  EXPECT_EQ(38, res.imag);
}

TEST(Complex, mulInline) {
  Complex<double> x, y;

  x.init(4, 5);
  x *= x;
  EXPECT_EQ(-9, x.real);
  EXPECT_EQ(40, x.imag);

  x.init(4, 5);
  y.init(6, 7);
  x *= y;
  EXPECT_EQ(-11, x.real);
  EXPECT_EQ(58, x.imag);
}

} // namespace math
