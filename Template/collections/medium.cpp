namespace cs {

template<typename T>
class MediumContainer {
public:
  inline void init() {
    while (!lc_.empty()) lc_.pop();
    while (!rc_.empty()) rc_.pop();
  }

  inline void add(const T& v) {
    if (lc_.empty()) {
      lc_.push(v);
      return;
    }
    if (SIZE(lc_) == SIZE(rc_)) {
      const T& r = rc_.top();
      if (v <= r) {
        lc_.push(v);
      } else {
        lc_.push(r);
        rc_.pop();
        rc_.push(v);
      }
    } else {
      const T& l = lc_.top();
      if (l <= v) {
        rc_.push(v);
      } else {
        rc_.push(l);
        lc_.pop();
        lc_.push(v);
      }
    }
  }

  inline T popMedium() {
    T res = lc_.top();
    lc_.pop();
    if (SIZE(lc_) < SIZE(rc_)) {
      lc_.push(rc_.top());
      rc_.pop();
    }
    return res;
  }

  inline T medium() const { return lc_.top(); }

private:
  priority_queue<T> lc_;
  MINHEAP<T> rc_;
}; // class MediumContainer
} // namespace cs
