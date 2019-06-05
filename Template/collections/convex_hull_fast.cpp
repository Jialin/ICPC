namespace cs {

template <typename T = int> class ConvexHullTricksFast {
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
    LD x;
    while (true) {
      x = CAST<LD>(b - topB_()) / (topA_() - a);
      if (xs_.empty() || (addToBack_ && xs_.back() < x) ||
          (!addToBack_ && x < xs_.front())) {
        break;
      }
      pop_();
    }
    add_(a, b, x);
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
    xs_.clear();
  }

  inline T topA_() { return addToBack_ ? as_.back() : as_.front(); }

  inline T topB_() { return addToBack_ ? bs_.back() : bs_.front(); }

  inline void pop_back_() {
    as_.pop_back();
    bs_.pop_back();
    if (!xs_.empty()) {
      xs_.pop_back();
    }
  }

  inline void pop_front_() {
    as_.pop_front();
    bs_.pop_front();
    if (!xs_.empty()) {
      xs_.pop_front();
    }
  }

  inline void pop_() {
    if (addToBack_) {
      pop_back_();
    } else {
      pop_front_();
    }
  }

  inline void add_(T a, T b, LD x) {
    if (addToBack_) {
      as_.push_back(a);
      bs_.push_back(b);
      xs_.push_back(x);
    } else {
      as_.push_front(a);
      bs_.push_front(b);
      xs_.push_front(x);
    }
  }

  inline int queryIdx_(T x) {
    if (!queryOrder_) {
      return queryIdxRandom(x);
    }
    if (queryOrder_ > 0) {
      for (; !xs_.empty() && xs_.front() < x; pop_front_()) {
      }
      return 0;
    } else {
      for (; !xs_.empty() && x < xs_.back(); pop_back_()) {
      }
      return SIZE(xs_);
    }
  }

  inline int queryIdxRandom(T x) {
    if (xs_.empty() || x < xs_.front()) {
      return 0;
    }
    int res = 0;
    for (int lower = 1, upper = SIZE(xs_); lower < upper;) {
      int medium = (lower + upper) >> 1;
      if (xs_[medium] < x) {
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
  deque<LD> xs_;
  bool isMax_, addToBack_;
  int queryOrder_;
}; // class ConvexHullTricks
} // namespace cs

using cs::ConvexHullTricksFast;
