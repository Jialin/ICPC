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

template <typename T> class MaxConvexHullTricksAddIncreasing {
private:
  class Line {
  public:
    T a, b, x;

    inline Line(T a_, T b_, T x_) : a(a_), b(b_), x(x_) {}
  };

  vector<Line> lines;

public:
  inline void init(int n = -1) {
    lines.clear();
    if (n > 0) {
      lines.reserve(n);
    }
  }

  inline void add(T a, T b) {
    static T inf = numeric_limits<T>::min();
    if (lines.empty()) {
      lines.emplace_back(a, b, inf);
      return;
    }
    const auto &lastLine = lines.back();
    if (lastLine.a == a) {
      if (b > lastLine.b) {
        lines.pop_back();
      } else {
        return;
      }
    }
    T x = inf;
    while (!lines.empty()) {
      const auto &line = lines.back();
      x = floorDiv(b - line.b, line.a - a);
      if (lines.size() == 1 || line.x < x) {
        break;
      }
      lines.pop_back();
    }
    lines.emplace_back(a, b, x);
  }

  inline const Line &queryLine(T x) const {
    return *(
        upper_bound(lines.begin(), lines.end(), x,
                    [](const T x_, const Line &line) { return x_ <= line.x; }) -
        1);
  }

  inline T query(T x) const {
    if (lines.empty()) {
      static T inf = numeric_limits<T>::min();
      return inf;
    }
    const auto &line = queryLine(x);
    return line.a * x + line.b;
  }

  inline int size() const { return static_cast<int>(lines.size()); }

  inline typename vector<Line>::iterator begin() { return lines.begin(); }
  inline typename vector<Line>::iterator end() { return lines.end(); }
  inline typename vector<Line>::reverse_iterator rbegin() {
    return lines.rbegin();
  }
  inline typename vector<Line>::reverse_iterator rend() { return lines.rend(); }
};

} // namespace collections