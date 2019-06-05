namespace math {

template <typename T> inline T gcd(T a, T b) {
  a = abs(a);
  b = abs(b);
  while (a && b) {
    if (a >= b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  return a + b;
}
} // namespace math

namespace math {

namespace {

template <typename T> inline bool cmp_(T num1, T den1, T num2, T den2) {
  if (!num2) {
    return false;
  }
  if (!num1) {
    return true;
  }
  bool overflow1 = LLONG_MAX / num1 < den2;
  bool overflow2 = LLONG_MAX / den1 < num2;
  if (!overflow1 && !overflow2) {
    return CAST<LL>(num1) * den2 < CAST<LL>(num2) * den1;
  }
  if (overflow1 && !overflow2) {
    return false;
  }
  if (!overflow1 && overflow2) {
    return true;
  }
  T v1 = num1 / den1;
  T v2 = num2 / den2;
  if (v1 != v2) {
    return v1 < v2;
  }
  num1 %= den1;
  num2 %= den2;
  if (!num2) {
    return false;
  }
  if (!num1) {
    return true;
  }
  return cmp_(den2, num2, den1, num1);
}
} // namespace

template <typename T> inline bool cmpFraction(T num1, T den1, T num2, T den2) {
  if (den1 < 0) {
    num1 = -num1;
    den1 = -den1;
  }
  if (den2 < 0) {
    num2 = -num2;
    den2 = -den2;
  }
  if (num1 < 0 && num2 < 0) {
    return cmp_(-num2, den2, -num1, den1);
  }
  if (num1 < 0) {
    return true;
  }
  if (num2 < 0) {
    return false;
  }
  return cmp_(num1, den1, num2, den2);
}
} // namespace math

namespace cs {

template <typename T = int> class ConvexHullTricks {
public:
  inline void initMaxAddDecreasingQueryRand() {
    init_(true /* isMax */, false /* addIncreasing */, 0 /* queryOrder */);
  }

  inline void initMaxAddDecreasingQueryDecreasing() {
    init_(true /* isMax */, false /* addIncreasing */, -1 /* queryOrder */);
  }

  inline void add(T a, T b) {
    if (as_.empty()) {
      as_.push_back(a);
      bs_.push_back(b);
      return;
    }
    if (topA_() == a) {
      if ((isMax_ && b <= topB_()) || (!isMax_ && b >= topB_())) {
        return;
      }
      pop_();
    }
    T num, den;
    while (true) {
      num = b - topB_();
      den = topA_() - a;
      if (nums_.empty() ||
          (addToBack_ &&
           math::cmpFraction(nums_.back(), dens_.back(), num, den)) ||
          (!addToBack_ &&
           math::cmpFraction(num, den, nums_.front(), dens_.front()))) {
        break;
      }
      pop_();
    }
    add_(a, b, num, den);
  }

  inline T query(T x, T defaultRes = 0) {
    if (as_.empty()) {
      return defaultRes;
    }
    int idx = queryIdx_(x);
    return as_[idx] * x + bs_[idx];
  }

private:
  inline void init_(bool isMax, bool addIncreasing, int queryOrder) {
    isMax_ = isMax;
    queryOrder_ = queryOrder;
    addToBack_ = isMax == addIncreasing;
    if (addToBack_) {
      assert(queryOrder_ >= 0);
    } else {
      assert(queryOrder_ <= 0);
    }
    as_.clear();
    bs_.clear();
    nums_.clear();
    dens_.clear();
  }

  inline T topA_() { return addToBack_ ? as_.back() : as_.front(); }

  inline T topB_() { return addToBack_ ? bs_.back() : bs_.front(); }

  inline void pop_back_() {
    as_.pop_back();
    bs_.pop_back();
    if (!nums_.empty()) {
      nums_.pop_back();
      dens_.pop_back();
    }
  }

  inline void pop_front_() {
    as_.pop_front();
    bs_.pop_front();
    if (!nums_.empty()) {
      nums_.pop_front();
      dens_.pop_front();
    }
  }

  inline void pop_() {
    if (addToBack_) {
      pop_back_();
    } else {
      pop_front_();
    }
  }

  inline bool cmpJointAndX_(int idx, T x) {
    return math::cmpFraction(nums_[idx], dens_[idx], x, CAST<T>(1));
  }

  inline void add_(T a, T b, T num, T den) {
    if (addToBack_) {
      as_.push_back(a);
      bs_.push_back(b);
      nums_.push_back(num);
      dens_.push_back(den);
    } else {
      as_.push_front(a);
      bs_.push_front(b);
      nums_.push_front(num);
      dens_.push_front(den);
    }
  }

  inline int queryIdx_(T x) {
    if (!queryOrder_) {
      return queryIdxRandom(x);
    }
    if (queryOrder_ > 0) {
      for (; !nums_.empty() && cmpJointAndX_(0, x); pop_front_()) {
      }
      return 0;
    } else {
      for (; !nums_.empty() && !cmpJointAndX_(SIZE(nums_) - 1, x);
           pop_back_()) {
      }
      return SIZE(nums_);
    }
  }

  inline int queryIdxRandom(T x) {
    if (nums_.empty() || !cmpJointAndX_(0, x)) {
      return 0;
    }
    int res = 0;
    for (int lower = 1, upper = SIZE(nums_); lower < upper;) {
      int medium = (lower + upper) >> 1;
      if (cmpJointAndX_(medium, x)) {
        res = medium;
        lower = medium + 1;
      } else {
        upper = medium;
      }
    }
    return res + 1;
  }

  // y = ax + b
  deque<T> as_, bs_;
  // joints at x axis
  deque<T> nums_, dens_;
  bool isMax_, addToBack_;
  int queryOrder_;
}; // class ConvexHullTricks
} // namespace cs

using cs::ConvexHullTricks;
