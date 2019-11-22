namespace collections {

template <typename T, typename CMP_UINT_T = uint64_t> class LiChaoTree {
public:
  inline void initQueryMax(bool queryMax_,
                           const vector<T> &orderedUniqueQueries) {
    queryMax = queryMax_;
    queries = orderedUniqueQueries;
    n = static_cast<int>(orderedUniqueQueries.size());
    capacity = n << 2;
    refresh();
  }

  inline void refresh() {
    as.resize(capacity);
    bs.resize(capacity);
    touched.assign(capacity, false);
  }

  inline void add(T a, T b) {
    if (!queryMax) {
      a = -a;
      b = -b;
    }
    int idx = 1, lower = 0, upper = n;
    while (true) {
      if (!touched[idx]) {
        as[idx] = a;
        bs[idx] = b;
        touched[idx] = true;
        break;
      }
      bool lowerAbove = isAbove(a, b, as[idx], bs[idx], queries[lower]);
      bool upperAbove = isAbove(a, b, as[idx], bs[idx], queries[upper - 1]);
      if (!(lowerAbove ^ upperAbove)) {
        if (lowerAbove) {
          as[idx] = a;
          bs[idx] = b;
        }
        break;
      }
      if (lower + 1 == upper) {
        break;
      }
      int medium = (lower + upper) >> 1;
      bool mediumAbove = isAbove(a, b, as[idx], bs[idx], queries[medium]);
      if (mediumAbove) {
        swap(as[idx], a);
        swap(bs[idx], b);
      }
      idx <<= 1;
      if (lowerAbove ^ mediumAbove) {
        upper = medium;
      } else {
        idx |= 1;
        lower = medium;
      }
    }
  }

  inline T query(T x) const {
    int idx = static_cast<int>(lower_bound(queries.begin(), queries.end(), x) -
                               queries.begin());
    assert(idx < static_cast<int>(queries.size()) && queries[idx] == x);
    return queryIdx(idx);
  }

  inline T queryIdx(int queryIdx) const {
    assert(touched[1]);
    T x = queries[queryIdx];
    T res = as[1] * x + bs[1];
    int idx = 1, lower = 0, upper = n;
    while (true) {
      if (idx > 1 && touched[idx]) {
        res = max(res, as[idx] * x + bs[idx]);
      }
      if (lower + 1 == upper) {
        break;
      }
      idx <<= 1;
      int medium = (lower + upper) >> 1;
      if (medium <= queryIdx) {
        idx |= 1;
        lower = medium;
      } else {
        upper = medium;
      }
    }
    return queryMax ? res : -res;
  }

private:
  bool queryMax;
  vector<T> queries;
  int n, capacity;
  // Convex hull lines of the interval
  vector<T> as, bs;
  vector<bool> touched;

  inline bool isProductOverflow(CMP_UINT_T a, CMP_UINT_T b) {
    if (!a || !b) {
      return false;
    }
    return a > numeric_limits<CMP_UINT_T>::max() / b;
  }

  inline void product(CMP_UINT_T a, CMP_UINT_T b, CMP_UINT_T &high,
                      CMP_UINT_T &low) {
    int halfL = numeric_limits<CMP_UINT_T>::digits >> 1;
    CMP_UINT_T halfMask = numeric_limits<CMP_UINT_T>::max() >> halfL;
    CMP_UINT_T aHigh = a >> halfL, aLow = a & halfMask;
    CMP_UINT_T bHigh = b >> halfL, bLow = b & halfMask;
    high = aHigh * bHigh;
    low = aLow * bLow;
    CMP_UINT_T ab = aHigh * bLow, ba = bHigh * aLow;
    high += (ab >> halfL) + (ba >> halfL);
    CMP_UINT_T lowHigh = (low >> halfL) + (ab & halfMask) + (ba & halfMask);
    high += lowHigh >> halfL;
    low = ((lowHigh & halfMask) << halfL) + (low & halfMask);
  }

  inline int sgn(CMP_UINT_T a, CMP_UINT_T b) {
    return a < b ? -1 : a == b ? 0 : 1;
  }

  inline int sgnUnsignedProduct(CMP_UINT_T a, CMP_UINT_T b, CMP_UINT_T c,
                                CMP_UINT_T d) {
    bool overflowAB = isProductOverflow(a, b);
    bool overflowCD = isProductOverflow(c, d);
    if (overflowAB) {
      if (overflowCD) {
        CMP_UINT_T high1, low1, high2, low2;
        product(a, b, high1, low1);
        product(c, d, high2, low2);
        int sgnHigh = sgn(high1, high2);
        return sgnHigh ? sgnHigh : sgn(low1, low2);
      } else {
        return 1;
      }
    } else {
      if (overflowCD) {
        return -1;
      } else {
        return sgn(a * b, c * d);
      }
    }
  }

  inline int sgnProduct(T a, T b, T c, T d) {
    if (b < 0) {
      a = -a;
      b = -b;
    }
    if (d < 0) {
      c = -c;
      d = -d;
    }
    if (a < 0) {
      if (c < 0) {
        return -sgnUnsignedProduct(-a, b, -c, d);
      } else {
        return -1;
      }
    } else {
      if (c < 0) {
        return 1;
      } else {
        return sgnUnsignedProduct(a, b, c, d);
      }
    }
  }

  inline bool isAbove(T a1, T b1, T a2, T b2, T x) {
    return sgnProduct(a1 - a2, x, b2 - b1, 1) > 0;
  }
};

} // namespace collections
