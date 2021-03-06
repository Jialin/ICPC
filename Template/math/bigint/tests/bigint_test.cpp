#include "gtest/gtest.h"

#define BIGINT_ALL
#include "math/bigint/bigint_macros.h"

#include "math/bigint/bigint.h"

using namespace std;

namespace math {

TEST(BigInt, initCharArray) {
  BigInt<4, int> v;

  string small("1234567890");
  v.initCharArray(small.c_str());
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(7890, v[0]);
  EXPECT_EQ(3456, v[1]);
  EXPECT_EQ(12, v[2]);

  string large("12345678901234567890");
  v.initCharArray(large.c_str(), large.size());
  ASSERT_EQ(5, v.size());
  EXPECT_EQ(7890, v[0]);
  EXPECT_EQ(3456, v[1]);
  EXPECT_EQ(9012, v[2]);
  EXPECT_EQ(5678, v[3]);
  EXPECT_EQ(1234, v[4]);

  string zero("0000000");
  v.initCharArray(zero.c_str());
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(0, v[0]);
}

TEST(BigInt, initInt) {
  BigInt<4, int> v;

  v.initInt(0);
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(0, v[0]);

  v.initInt(1238183825);
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(3825, v[0]);
  EXPECT_EQ(3818, v[1]);
  EXPECT_EQ(12, v[2]);

  v.initInt(10000100001000010000ULL);
  ASSERT_EQ(5, v.size());
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(1, v[1]);
  EXPECT_EQ(10, v[2]);
  EXPECT_EQ(100, v[3]);
  EXPECT_EQ(1000, v[4]);
}

TEST(BigInt, initMul) {
  BigInt<4, int> a, b, res;

  a = 0;
  b = 0;
  res.initMul(a, b);
  ASSERT_EQ(1, res.size());
  EXPECT_EQ(0, res[0]);

  a = "1";
  b = "0";
  res.initMul(a, b);
  ASSERT_EQ(1, res.size());
  EXPECT_EQ(0, res[0]);

  a = "1833811";
  b = "0";
  res.initMul(a, b);
  ASSERT_EQ(1, res.size());
  EXPECT_EQ(0, res[0]);

  a = "12";
  b = "77";
  res.initMul(a, b);
  ASSERT_EQ(1, res.size());
  EXPECT_EQ(924, res[0]);

  a = "1833811";
  b = "1847182";
  res.initMul(a, b);
  ASSERT_EQ(4, res.size());
  EXPECT_EQ(602, res[0]);
  EXPECT_EQ(8267, res[1]);
  EXPECT_EQ(3873, res[2]);
  EXPECT_EQ(3, res[3]);

  a = 12;
  b = 12;
  res.initMul(a, b);
  ASSERT_EQ(1, res.size());
  EXPECT_EQ(144, res[0]);

  a = 2;
  b = "2222222222222222";
  res.initMul(a, b);
  ASSERT_EQ(4, res.size());
  EXPECT_EQ(4444, res[0]);
  EXPECT_EQ(4444, res[1]);
  EXPECT_EQ(4444, res[2]);
  EXPECT_EQ(4444, res[3]);

  a = "12838183401841";
  b = "2222222222222222";
  res.initMul(a, b);
  ASSERT_EQ(8, res.size());
  EXPECT_EQ(702, res[0]);
  EXPECT_EQ(2591, res[1]);
  EXPECT_EQ(7026, res[2]);
  EXPECT_EQ(5552, res[3]);
  EXPECT_EQ(4853, res[4]);
  EXPECT_EQ(2964, res[5]);
  EXPECT_EQ(8529, res[6]);
  EXPECT_EQ(2, res[7]);

  BigInt<9, int64_t, long double> a9, b9, res9;
  a9 = "999999999999999999999";
  b9 = "8123881931004020101941";
  res9.initMul(a9, b9);
  ASSERT_EQ(5, res9.size());
  EXPECT_EQ(979898059, res9[0]);
  EXPECT_EQ(118068995, res9[1]);
  EXPECT_EQ(101932876, res9[2]);
  EXPECT_EQ(931004020, res9[3]);
  EXPECT_EQ(8123881, res9[4]);
}

TEST(BigInt, assign) {
  BigInt<4, int> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<4, int> b = a;
  ASSERT_EQ(5, b.size());
  EXPECT_EQ(7890, b[0]);
  EXPECT_EQ(3456, b[1]);
  EXPECT_EQ(9012, b[2]);
  EXPECT_EQ(5678, b[3]);
  EXPECT_EQ(1234, b[4]);
}

TEST(BigInt, assignCharArray) {
  BigInt<4, int> v;
  v = "12387576124950030100";

  ASSERT_EQ(5, v.size());
  EXPECT_EQ(100, v[0]);
  EXPECT_EQ(5003, v[1]);
  EXPECT_EQ(1249, v[2]);
  EXPECT_EQ(7576, v[3]);
  EXPECT_EQ(1238, v[4]);
}

TEST(BigInt, assignString) {
  BigInt<4, int> v;
  v = string("13412413566103931");

  ASSERT_EQ(5, v.size());
  EXPECT_EQ(3931, v[0]);
  EXPECT_EQ(6610, v[1]);
  EXPECT_EQ(4135, v[2]);
  EXPECT_EQ(3412, v[3]);
  EXPECT_EQ(1, v[4]);
}

TEST(BigInt, assignInt) {
  BigInt<4, int> v;
  v = 12351491204118411LL;

  ASSERT_EQ(5, v.size());
  EXPECT_EQ(8411, v[0]);
  EXPECT_EQ(411, v[1]);
  EXPECT_EQ(4912, v[2]);
  EXPECT_EQ(2351, v[3]);
  EXPECT_EQ(1, v[4]);
}

TEST(BigInt, addInline) {
  BigInt<4, int> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<4, int> b;
  string bStr("12384813");
  b.initCharArray(bStr.c_str(), bStr.size());

  BigInt<4, int> c = a;
  c += b;
  ASSERT_EQ(5, c.size());
  EXPECT_EQ(2703, c[0]);
  EXPECT_EQ(4695, c[1]);
  EXPECT_EQ(9012, c[2]);
  EXPECT_EQ(5678, c[3]);
  EXPECT_EQ(1234, c[4]);

  c += a;
  ASSERT_EQ(5, c.size());
  EXPECT_EQ(593, c[0]);
  EXPECT_EQ(8152, c[1]);
  EXPECT_EQ(8024, c[2]);
  EXPECT_EQ(1357, c[3]);
  EXPECT_EQ(2469, c[4]);
}

TEST(BigInt, subInline) {
  BigInt<9> a;
  a = "12345678901234567890";
  BigInt<9> b;
  b = "12384812331371743";
  a -= b;
  ASSERT_EQ(3, a.size());
  EXPECT_EQ(903196147, a[0]);
  EXPECT_EQ(333294088, a[1]);
  EXPECT_EQ(12, a[2]);

  b = "12333294088371371738";
  a -= b;
  ASSERT_EQ(1, a.size());
  EXPECT_EQ(531824409, a[0]);

  b = "531824409";
  a -= b;
  ASSERT_EQ(1, a.size());
  EXPECT_EQ(0, a[0]);
}

TEST(BigInt, addInlineInt) {
  BigInt<9> v;
  v = "12345678901234567890";

  v += 0;
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(234567890, v[0]);
  EXPECT_EQ(345678901, v[1]);
  EXPECT_EQ(12, v[2]);

  v += 1838810371747142948LL;
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(981710838, v[0]);
  EXPECT_EQ(184489272, v[1]);
  EXPECT_EQ(14, v[2]);
}

TEST(BigInt, mulInlineInt) {
  BigInt<9> v;

  v = "182378471831341";
  v *= 2;
  ASSERT_EQ(2, v.size());
  EXPECT_EQ(943662682, v[0]);
  EXPECT_EQ(364756, v[1]);

  v *= 128348578;
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(346366196, v[0]);
  EXPECT_EQ(35034731, v[1]);
  EXPECT_EQ(46816, v[2]);

  v *= 0;
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(0, v[0]);
}

TEST(BigInt, modInline) {
  BigInt<9> x, y, divRes;

  x = "1827461738161";
  y = "1";
  x.modDivInline(y, divRes);
  ASSERT_EQ(1, x.size());
  EXPECT_EQ(0, x[0]);
  ASSERT_EQ(2, divRes.size());
  EXPECT_EQ(461738161, divRes[0]);
  EXPECT_EQ(1827, divRes[1]);

  x = "1827461738161";
  y = "5938372";
  x.modDivInline(y, divRes);
  ASSERT_EQ(1, x.size());
  EXPECT_EQ(4953997, x[0]);
  ASSERT_EQ(1, divRes.size());
  EXPECT_EQ(307737, divRes[0]);

  x = "1827461738161";
  y = "1313344566778333010284";
  x.modDivInline(y, divRes);
  ASSERT_EQ(2, x.size());
  EXPECT_EQ(461738161, x[0]);
  EXPECT_EQ(1827, x[1]);
  ASSERT_EQ(1, divRes.size());
  EXPECT_EQ(0, divRes[0]);

  x = "131334456677838183333010284";
  y = "1827461738161";
  x.modDivInline(y, divRes);
  ASSERT_EQ(2, x.size());
  EXPECT_EQ(232549430, x[0]);
  EXPECT_EQ(692, x[1]);
  ASSERT_EQ(2, divRes.size());
  EXPECT_EQ(144430614, divRes[0]);
  EXPECT_EQ(71867, divRes[1]);

  x = "4061190159652342805";
  y = "1014607205739078075";
  x.modDivInline(y, divRes);
  ASSERT_EQ(2, x.size());
  EXPECT_EQ(696030505, x[0]);
  EXPECT_EQ(2761336, x[1]);
  ASSERT_EQ(1, divRes.size());
  EXPECT_EQ(4, divRes[0]);
}

TEST(BigInt, divModInlineInt) {
  BigInt<9> v;
  v = "182378471831341231241";
  EXPECT_EQ(2, v.divModInlineInt(3));
  ASSERT_EQ(3, v.size());
  EXPECT_EQ(780410413, v[0]);
  EXPECT_EQ(792823943, v[1]);
  EXPECT_EQ(60, v[2]);

  EXPECT_EQ(11173, v.divModInlineInt(18284));
  ASSERT_EQ(2, v.size());
  EXPECT_EQ(270607110, v[0]);
  EXPECT_EQ(3324919, v[1]);

  EXPECT_EQ(970607110, v.divModInlineInt(1100000000));
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(3022653, v[0]);

  EXPECT_EQ(3022653, v.divModInlineInt(1100000000));
  ASSERT_EQ(1, v.size());
  EXPECT_EQ(0, v[0]);
}

TEST(BigInt, modInt) {
  BigInt<9> v;
  v = "182378471831341231241";
  EXPECT_EQ(0, v % 1);
  EXPECT_EQ(1, v % 2);
  EXPECT_EQ(1, v % 10);
  EXPECT_EQ(62673313, v % 123837817);
}

TEST(BigInt, cmp) {
  BigInt<9> a;
  string aStr("12345678901234567890");
  a.initCharArray(aStr.c_str(), aStr.size());

  BigInt<9> b;
  string bStr("12384813");
  b.initCharArray(bStr.c_str(), bStr.size());

  BigInt<9> c;
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
  BigInt<4, int> v;
  v = "12345678901234";

  EXPECT_EQ(1, v.cmp(0));
  EXPECT_EQ(1, v.cmp(12345678901233LL));
  EXPECT_EQ(0, v.cmp(12345678901234LL));
  EXPECT_EQ(-1, v.cmp(12345678901235LL));
  EXPECT_EQ(-1, v.cmp(123456789012351241LL));
  EXPECT_EQ(-1, v.cmp(12345678901235124112ULL));
}

TEST(BigInt, digitCount) {
  BigInt<4, int> v;
  v = "00000";
  EXPECT_EQ(1, v.digitCount());
  v = "9";
  EXPECT_EQ(1, v.digitCount());
  v = "10";
  EXPECT_EQ(2, v.digitCount());
  v = "12345678901234";
  EXPECT_EQ(14, v.digitCount());
  v = "123456789012345";
  EXPECT_EQ(15, v.digitCount());
  v = "12345678901234567";
  EXPECT_EQ(17, v.digitCount());
  v = "123456789012345678";
  EXPECT_EQ(18, v.digitCount());
  v = "1234567890123456789";
  EXPECT_EQ(19, v.digitCount());
}

TEST(BigInt, digitSum) {
  BigInt<4, int> v;

  v = "00000";
  EXPECT_EQ(0, v.digitSum());

  v = "12345678901234";
  EXPECT_EQ(55, v.digitSum());

  v = "123456789012349";
  EXPECT_EQ(64, v.digitSum());
}

TEST(BigInt, outputCharArray) {
  BigInt<9> v;
  char s[100];

  v = "0000";
  v.outputCharArray(s);
  EXPECT_EQ("0", static_cast<string>(s));

  v = "1834388473749184733871841";
  v.outputCharArray(s);
  EXPECT_EQ("1834388473749184733871841", static_cast<string>(s));

  v = "100020300000310000300000000100002020";
  v.outputCharArray(s);
  EXPECT_EQ("100020300000310000300000000100002020", static_cast<string>(s));
}

TEST(BigInt, gcdInline) {
  BigInt<9> x, y;
  x = "45100439945872875162588853040";
  y = "262846577632689827002596945105";
  x.gcdInline(y);
  ASSERT_EQ(1, x.size());
  EXPECT_EQ(5, x[0]);

  x = "43797171767909538775377586789912267051678004886825696794901";
  y = "824115863980304742029251596393600152537089467162";
  x.gcdInline(y);
  ASSERT_EQ(4, x.size());
  EXPECT_EQ(727483821, x[0]);
  EXPECT_EQ(473738383, x[1]);
  EXPECT_EQ(383747178, x[2]);
  EXPECT_EQ(1838, x[3]);
}

} // namespace math
