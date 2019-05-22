namespace cs {

template<typename T, typename Compare = less<T>>
class LIS {
public:
  inline void init(int n) {
    lis_.clear();
    lis_.reserve(n);
    result_ = 0;
  }

  inline int locateIdx(const T& v) const {
    return CAST<int>(lower_bound(lis_.begin(), lis_.end(), v, cmp_) - lis_.begin());
  }

  inline void add(const T& v) {
    int idx = locateIdx(v);
    if (idx == SIZE(lis_)) {
      lis_.push_back(v);
    } else {
      lis_[idx] = v;
    }
  }

  inline int length() const { return SIZE(lis_); }

private:
  vector<T> lis_;
  int result_;
  Compare cmp_;
}; // class LIS
} // namespace cs
