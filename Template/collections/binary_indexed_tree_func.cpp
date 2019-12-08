namespace collections {

class BinaryIndexedTreeFunc {
private:
  int n;

public:
  inline void init(int n_) { n = n_; }

  inline void update(int idx, const function<void(int)> &updater) {
    for (; idx < n; idx |= idx + 1) {
      updater(idx);
    }
  }

  inline void query(int idx, const function<void(int)> &queryProcessor) {
    for (; idx >= 0; idx = (idx & (idx + 1)) - 1) {
      queryProcessor(idx);
    }
  }
};

} // namespace collections
