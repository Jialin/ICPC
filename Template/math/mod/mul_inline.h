#pragma once

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline void mulModInline(V& res, V x, const V& mod) {
  if (!res || !x) {
    res = 0;
  } else if (res < mod / x) {
    res *= x;
  } else {
    res = static_cast<V_SQR>(res) * x % mod;
  }
}

} // namespace math
