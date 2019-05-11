namespace cs {

/** Add and remove numbers from the counter, the counter will keep track of the number of unqiue numbers. */
class UniqueCounterSimple {
public:
  inline void init(int n) {
    uniqueCnt_ = 0;
    vs_.resize(n);
  }

  inline void update(int x, int v) {
    if (!vs_[x]) ++uniqueCnt_;
    vs_[x] += v;
    if (!vs_[x]) --uniqueCnt_;
  }

  inline int uniqueCnt() const { return uniqueCnt_; }
  inline int v(int x) const { return vs_[x]; }
  inline int n() const { return SIZE(vs_); }

private:
  int uniqueCnt_;
  vector<int> vs_;
}; // class UniqueCounter
} // namespace cs

namespace testing {

string toDisplay(const cs::UniqueCounterSimple& counter) {
  ostringstream ss;
  ss << "vs(" << counter.uniqueCnt() << "):";
  FOR(i, 0, counter.n()) {
    ss << counter.v(i) << ",";
  }
  ss << endl;
  return ss.str();
}
} // namespace testing
