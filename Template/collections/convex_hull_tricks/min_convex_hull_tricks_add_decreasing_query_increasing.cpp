// @autogen
namespace collections {

namespace {

/** floor(num/den) */
template <typename T> inline T floorDiv(T num, T den) {
  assert(den);
  T res = num / den;
  return (num ^ den) >= 0 ? res : res - static_cast<bool>(num % den);
}

} // namespace

template <typename T> class MinConvexHullTricksAddDecreasingQueryIncreasing {
private:
  class Line {
  public:
    T a, b, x;

    inline Line(T a_, T b_) : a(a_), b(b_), x(0) {}
  };

  inline void pushBack(T a, T b) {
    lines.emplace_back(a, b);
    ++tail;
  }

  inline void popBack() {
    lines.pop_back();
    --tail;
  }

public:
  inline void init(int n = -1) {
    lines.clear();
    head = 0;
    tail = 0;
    if (n > 0) {
      lines.reserve(n);
    }
  }

  inline void add(T a, T b) {
    if (empty()) {
      pushBack(a, b);
      return;
    }
    const auto &cl = lines.back();
    if (cl.a == a) {
      if (cl.b <= b) {
        return;
      }
      popBack();
    }
    T x;
    while (true) {
      const auto &l = lines.back();
      x = floorDiv(b - l.b, l.a - a);
      if (head + 1 >= tail || lines[tail - 2].x < x) {
        break;
      }
      popBack();
    }
    if (!empty()) {
      auto &l = lines.back();
      l.x = x;
    }
    pushBack(a, b);
  }

  inline int queryLineIdx(T x) {
    for (; head + 1 < tail && x > lines[head].x; ++head) {
    }
    return head;
  }

  inline T query(T x) {
    assert(!empty());
    const auto &l = lines[queryLineIdx(x)];
    return l.a * x + l.b;
  }

  inline bool empty() const { return head >= tail; }

  vector<Line> lines;
  int head, tail;
};

} // namespace collections