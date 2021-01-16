#pragma once

#include "math/complex/complex_macros.h" // INCLUDE
#include "math/fft/fft_utils_macros.h"

#include "math/bit/next_pow2_32.h"
#include "math/complex/complex.h"
#include "math/constants/pi.h"

using namespace std;

namespace math {

template<typename T = double>
struct FFTUtils {
  inline static FFTUtils& instance() {
    static FFTUtils instance;
    return instance;
  }

  inline void initCapacity(int capacity) {
    if (_revs.size() >= capacity) {
      return;
    }
    int pow2 = nextPow2_32(max(capacity, 2));
    _revs.reserve(pow2);
    _roots.reserve(pow2);
    if (_revs.size() < 2) {
      _revs.resize(2);
      _revs[0] = 0;
      _revs[1] = 1;
      _roots.resize(2);
      // => COMPLEX_INIT
      _roots[0].init(0, 0);
      _roots[1].init(1, 0);
    }
    int oldPow2 = _revs.size(), lgN = __builtin_ctz(pow2);
    _revs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _revs[i] = (_revs[i >> 1] >> 1) + ((i & 1) << (lgN - 1));
    }
    _roots.resize(pow2);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      T baseAngle = PI / i;
      for (int j = i, k = 1; j < i << 1; j += 2, k += 2) {
        _roots[j] = _roots[j >> 1];
        // => COMPLEX_INIT_POLAR
        _roots[j | 1].initPolar(1, baseAngle * k);
      }
    }
  }

  inline void fft(vector<Complex<T>>& cs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? cs.size() : n);
    initCapacity(pow2);
    _expand(cs, pow2);
    if (inverse) {
      reverse(cs.begin() + 1, cs.begin() + pow2);
      for (int i = 0; i < pow2; ++i) {
        // => COMPLEX_DIV_INLINE_DOUBLE
        cs[i] /= pow2;
      }
    }
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = _revs[i] >> shift;
      if (i < j) {
        swap(cs[i], cs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0; i < pow2; i += l << 1) {
        for (int j = 0; j < l; ++j) {
          // => COMPLEX_MUL
          Complex<T> c = cs[i + j + l] * _roots[j + l];
          // => COMPLEX_INIT_SUB
          cs[i + j + l].initSub(cs[i + j], c);
          // => COMPLEX_ADD_INLINE
          cs[i + j] += c;
        }
      }
    }
  }

  inline void _expand(vector<Complex<T>>& cs, int pow2) {
    int n = cs.size();
    cs.resize(pow2);
    for (size_t i = n; i < pow2; ++i) {
      cs[i].init(0, 0);
    }
  }

  vector<int> _revs;
  vector<Complex<T>> _roots;
};

} // namespace math
