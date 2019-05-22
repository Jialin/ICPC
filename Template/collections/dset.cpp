namespace cs {

class DisjointSet {
public:
  inline void init(int n) {
    p_.resize(n);
    fill(p_.begin(), p_.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p_[root] >= 0; root = p_[root]) {}
    while (p_[x] >= 0) {
      int tmp = p_[x];
      p_[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      if (p_[rootX] > p_[rootY]) swap(rootX, rootY);
      p_[rootX] += p_[rootY];
      p_[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) { return calcRoot(x) == calcRoot(y); }
  inline int calcSize(int x) { return -p_[calcRoot(x)]; }
  inline bool isRoot(int x) const { return p_[x] < 0; }
  inline int n() const { return SIZE(p_); }

private:
  vector<int> p_;
}; // class DisjointSet
} // namespace cs
