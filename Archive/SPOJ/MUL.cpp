#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

template<class T> using MINHEAP = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
using ULL = unsigned long long;

#define CAST static_cast
#define SIZE(v) (CAST<int>((v).size()))
#define BEGIN(v) ((v).begin())
#define END(v) ((v).end())
#define ALL(v) BEGIN(v),END(v)
#define SORT(v) sort(ALL(v))
#define UNIQUE(v) SORT(v);(v).erase(unique(ALL(v)),END(v))
#define INDEX(v,x) lower_bound(ALL(v),x)-BEGIN(v)
#define FOR(i,l,r) for(int i=(l);i<(r);++i)

#define FLUSH fflush(stdout)
#define ERR(...) fprintf(stderr, __VA_ARGS__)

namespace math {

template<typename T = double>
class Complex {
public:
  inline Complex(const T& real = 0, const T& imag = 0) : real_(real), imag_(imag) {}

  inline Complex<T> operator*(const Complex<T>& o) {
    return Complex(
        real_ * o.real_ - imag_ * o.imag_,
        real_ * o.imag_ + imag_ * o.real_);
  }

  inline void operator+=(const Complex<T>& o) {
    real_ += o.real_;
    imag_ += o.imag_;
  }

  inline void operator/=(const T& scale) {
    real_ /= scale;
    imag_ /= scale;
  }

  inline void init(const T& real = 0, const T& imag = 0) {
    real_ = real;
    imag_ = imag;
  }

  inline void initPolar(const T& r, const T& theta) {
    real_ = r * cos(theta);
    imag_ = r * sin(theta);
  }

  inline void initMul(const Complex<T>& x, const Complex<T>& y) {
    real_ = x.real_ * y.real_ - x.imag_ * y.imag_;
    imag_ = x.real_ * y.imag_ + x.imag_ * y.real_;
  }

  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real_ = x.real_ - y.real_;
    imag_ = x.imag_ - y.imag_;
  }

  inline T real() const { return real_; }
  inline T imag() const { return imag_; }
private:
  T real_;
  T imag_;
}; // class Complex
} // namespace math

namespace math {

namespace {
constexpr double kEPS = 1E-7;
} // namespace

template<typename T = double>
class FFT {
public:
  inline FFT()
      : ws_(unordered_map<int, vector<Complex<T>>>(32)),
        revs_(unordered_map<int, vector<int>>(32)) {}

  inline int mul(
      int n, vector<Complex<T>>& a,
      int m, vector<Complex<T>>& b,
      vector<Complex<T>>& c) {

    clean_(n, a);
    clean_(m, b);
    int nm = n + m - 1;
    int pow2 = 1 << (31 - __builtin_clz(nm));
    if (pow2 < nm) pow2 <<= 1;
    reset_(a, n, pow2);
    reset_(b, m, pow2);
    fft(pow2, a, false);
    fft(pow2, b, false);
    if (SIZE(c) < pow2) c.resize(pow2);
    FOR(i, 0, pow2) c[i].initMul(a[i], b[i]);
    fft(pow2, c, true);
    int res = pow2;
    clean_(res, c);
    return res;
  }

  inline void fft(int pow2, vector<Complex<T>>& vs, bool invert) {
    init_(pow2);
    swap_(pow2, vs);
    const auto& w = ws_[pow2];
    for (int l = 1; l < pow2; l <<= 1) {
      int l2 = l << 1, step = pow2 / l2;
      for (int i = 0; i < pow2; i += l2) {
        for (int j = 0, wIdx = invert ? pow2 : 0; j < l; ++j, wIdx += invert ? -step : step) {
          mul_.initMul(vs[i + j + l], w[wIdx]);
          vs[i + j + l].initSub(vs[i + j], mul_);
          vs[i + j] += mul_;
        }
      }
    }
    if (invert) {
      FOR(i, 0, pow2) vs[i] /= pow2;
    }
  }
private:
  inline void init_(int pow2) {
    if (ws_.count(pow2)) return ;
    auto& w = ws_[pow2];
    auto& rev = revs_[pow2];
    w.reserve(pow2 + 1);
    w.emplace_back(1, 0);
    base_.initPolar(1, acos(CAST<T>(-1)) * 2 / pow2);
    rev.resize(pow2);
    int logN = __builtin_ctz(pow2);
    FOR(i, 0, pow2) {
      w.push_back(w.back() * base_);
      rev[i] = 0;
      for (int j = i; j > 0; j &= j - 1) {
        rev[i] |= 1 << (logN - 1 - __builtin_ctz(j));
      }
    }
  }

  inline void swap_(int pow2, vector<Complex<T>>& vs) {
    const auto& rev = revs_[pow2];
    FOR(i, 0, pow2) if (i < rev[i]) swap(vs[i], vs[rev[i]]);
  }

  inline void clean_(int& n, const vector<Complex<T>>& vs) {
    if (!n) n = 1;
    for ( ; n > 1 && abs(vs[n - 1].real()) < 0.5 - kEPS; --n) {}
  }

  inline void reset_(vector<Complex<T>>& vs, int fromIdx, int toIdx) {
    FOR(i, fromIdx, toIdx) vs[i].init();
  }

  unordered_map<int, vector<Complex<T>>> ws_;
  unordered_map<int, vector<int>> revs_;
  Complex<T> mul_, base_;
}; // class FFT
} // namespace math

using COMPLEX_T = double;

const int TRUNK = 4;
const int POW10[TRUNK + 1] = {
    1,
    10,
    100,
    1000,
    10000,
};
const int BASE = POW10[TRUNK];
const int MAXN = 1 << 15;
const int MAXL = 10000;

math::FFT<COMPLEX_T> fft;
vector<math::Complex<COMPLEX_T>> a, b, c;
char token[MAXL + 1];

inline int init(vector<math::Complex<COMPLEX_T>>& vs) {
  scanf("%s", token);
  int n = CAST<int>(strlen(token));
  int res = 0;
  for (int i = n - 1; i >= 0; ) {
    int piece = 0;
    for (int j = 0; i >= 0 && j < TRUNK; ++j) {
      piece += (token[i--] - '0') * POW10[j];
    }
    vs[res++].init(piece);
  }
  return res;
}

vector<int> pieces;

inline void print(int n, const vector<math::Complex<COMPLEX_T>>& vs) {
  int res = 0;
  LL carry = 0;
  FOR(i, 0, n) {
    LL v = CAST<LL>(vs[i].real() + 0.5) + carry;
    carry = v / BASE;
    pieces[res++] = CAST<int>(v % BASE);
  }
  for ( ; carry > 0; carry /= BASE) {
    pieces[res++] = CAST<int>(carry % BASE);
  }
  printf("%d", pieces[res - 1]);
  for (int i = res - 2; i >= 0; --i) {
    printf("%0*d", TRUNK, pieces[i]);
  }
  putchar('\n');
}

int main() {
  a.resize(MAXN);
  b.resize(MAXN);
  pieces.resize(MAXN);
  int taskNumber; scanf("%d", &taskNumber);
  for (int taskIdx = 1; taskIdx <= taskNumber; taskIdx++) {
    int n = init(a);
    int m = init(b);
    int nm = fft.mul(n, a, m, b, c);
    print(nm, c);
  }
  return 0;
}

