#include "gtest/gtest.h"

#define BIGINT_ALL

#include "math/bigint.h"

using namespace std;

namespace math {

TEST(BigInt, initCharArray) {
  BigInt<> v;

  string small("1234567890");
  v.initCharArray(small.c_str());
  ASSERT_EQ(3, v._vs.size());
  EXPECT_EQ(7890, v._vs[0]);
  EXPECT_EQ(3456, v._vs[1]);
  EXPECT_EQ(12, v._vs[2]);

  string large("12345678901234567890");
  v.initCharArray(large.c_str(), large.size());
  ASSERT_EQ(5, v._vs.size());
  EXPECT_EQ(7890, v._vs[0]);
  EXPECT_EQ(3456, v._vs[1]);
  EXPECT_EQ(9012, v._vs[2]);
  EXPECT_EQ(5678, v._vs[3]);
  EXPECT_EQ(1234, v._vs[4]);

  string zero("0000000");
  v.initCharArray(zero.c_str());
  ASSERT_EQ(1, v._vs.size());
  EXPECT_EQ(0, v._vs[0]);
}

TEST(BigInt, initInt) {
  BigInt<> v;

  v.initInt(0);
  ASSERT_EQ(1, v._vs.size());
  EXPECT_EQ(0, v._vs[0]);

  v.initInt(1238183825);
  ASSERT_EQ(3, v._vs.size());
  EXPECT_EQ(3825, v._vs[0]);
  EXPECT_EQ(3818, v._vs[1]);
  EXPECT_EQ(12, v._vs[2]);

  v.initInt(10000100001000010000ULL);
  ASSERT_EQ(5, v._vs.size());
  EXPECT_EQ(0, v._vs[0]);
  EXPECT_EQ(1, v._vs[1]);
  EXPECT_EQ(10, v._vs[2]);
  EXPECT_EQ(100, v._vs[3]);
  EXPECT_EQ(1000, v._vs[4]);
}

TEST(BigInt, assign) {
  BigInt<> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<> b = a;
  ASSERT_EQ(5, b._vs.size());
  EXPECT_EQ(7890, b._vs[0]);
  EXPECT_EQ(3456, b._vs[1]);
  EXPECT_EQ(9012, b._vs[2]);
  EXPECT_EQ(5678, b._vs[3]);
  EXPECT_EQ(1234, b._vs[4]);
}

TEST(BigInt, assignCharArray) {
  BigInt<> v;
  v = "12387576124950030100";

  ASSERT_EQ(5, v._vs.size());
  EXPECT_EQ(100, v._vs[0]);
  EXPECT_EQ(5003, v._vs[1]);
  EXPECT_EQ(1249, v._vs[2]);
  EXPECT_EQ(7576, v._vs[3]);
  EXPECT_EQ(1238, v._vs[4]);
}

TEST(BigInt, assignString) {
  BigInt<> v;
  v = string("13412413566103931");

  ASSERT_EQ(5, v._vs.size());
  EXPECT_EQ(3931, v._vs[0]);
  EXPECT_EQ(6610, v._vs[1]);
  EXPECT_EQ(4135, v._vs[2]);
  EXPECT_EQ(3412, v._vs[3]);
  EXPECT_EQ(1, v._vs[4]);
}

TEST(BigInt, assignInt) {
  BigInt<> v;
  v = 12351491204118411LL;

  ASSERT_EQ(5, v._vs.size());
  EXPECT_EQ(8411, v._vs[0]);
  EXPECT_EQ(411, v._vs[1]);
  EXPECT_EQ(4912, v._vs[2]);
  EXPECT_EQ(2351, v._vs[3]);
  EXPECT_EQ(1, v._vs[4]);
}

TEST(BigInt, addInline) {
  BigInt<> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<> b;
  string bStr("12384813");
  b.initCharArray(bStr.c_str(), bStr.size());

  BigInt<> c = a;
  c += b;
  ASSERT_EQ(5, c._vs.size());
  EXPECT_EQ(2703, c._vs[0]);
  EXPECT_EQ(4695, c._vs[1]);
  EXPECT_EQ(9012, c._vs[2]);
  EXPECT_EQ(5678, c._vs[3]);
  EXPECT_EQ(1234, c._vs[4]);

  c += a;
  ASSERT_EQ(5, c._vs.size());
  EXPECT_EQ(593, c._vs[0]);
  EXPECT_EQ(8152, c._vs[1]);
  EXPECT_EQ(8024, c._vs[2]);
  EXPECT_EQ(1357, c._vs[3]);
  EXPECT_EQ(2469, c._vs[4]);
}

TEST(BigInt, cmp) {
  BigInt<> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<> b;
  string bStr("12384813");
  b.initCharArray(bStr.c_str(), bStr.size());

  BigInt<> c;
  string cStr("12345678901234567891");
  c.initCharArray(cStr.c_str(), cStr.size());

  EXPECT_EQ(0, a.cmp(a));
  EXPECT_EQ(1, a.cmp(b));
  EXPECT_EQ(-1, a.cmp(c));

  EXPECT_EQ(-1, b.cmp(a));
  EXPECT_EQ(0, b.cmp(b));
  EXPECT_EQ(-1, b.cmp(c));

  EXPECT_EQ(1, c.cmp(a));
  EXPECT_EQ(1, c.cmp(b));
  EXPECT_EQ(0, c.cmp(c));
}

TEST(BigInt, cmpInt) {
  BigInt<> v;
  v = "12345678901234";

  EXPECT_EQ(1, v.cmp(0));
  EXPECT_EQ(1, v.cmp(12345678901233LL));
  EXPECT_EQ(0, v.cmp(12345678901234LL));
  EXPECT_EQ(-1, v.cmp(12345678901235LL));
  EXPECT_EQ(-1, v.cmp(123456789012351241LL));
  EXPECT_EQ(-1, v.cmp(12345678901235124112LL));
}

TEST(BigInt, length) {
  BigInt<> v;

  v = "00000";
  EXPECT_EQ(1, v.length());

  v = "12345678901234";
  EXPECT_EQ(14, v.length());
}

} // namespace math
