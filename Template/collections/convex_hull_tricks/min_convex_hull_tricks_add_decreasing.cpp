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

template <typename T> class MinConvexHullTricksAddDecreasing {
private:
  class Line {
  public:
    T a, b, x;

    inline Line(T a_, T b_, T x_) : a(a_), b(b_), x(x_) {}
  };

public:
  inline void init() { lines.clear(); }

  inline void add(T a, T b) {
    static T inf = numeric_limits<T>::min();
    if (lines.empty()) {
      lines.emplace_back(a, b, inf);
      return;
    }
    const auto &line = lines.back();
    if (line.a == a) {
      if (b < line.b) {
        lines.pop_back();
      } else {
        return;
      }
    }
    T x;
    while (true) {
      line = lines.back();
      x = floorDiv(b - line.b, line.a - a);
      if (lines.size() == 1 || line.x < x) {
        break;
      }
      lines.pop_back();
    }
    lines.emplace_back(a, b, x);
  }

  inline int queryLineIdx(T x) {
    return static_cast<int>(
        lower_bound(lines.begin(), lines.end(), x,
                    [](const Line &line, const T x_) { return line.x < x_; }) -
        lines.begin());
  }

  inline T query(T x) {
    assert(!lines.empty());
    const auto &line = lines[queryLineIdx(x)];
    return line.a * x + line.b;
  }

  deque<Line> lines;
};

} // namespace collections