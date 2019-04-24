namespace cs {

class DisjointSet {
public:
  vector<int> p;

  inline void init(int n) {
    p.resize(n);
    fill(p.begin(), p.end(), -1);
  }

  inline int calcRoot(int x) {
    int root = x;
    for ( ; p[root] >= 0; root = p[root]) {}
    while (p[x] >= 0) {
      int tmp = p[x];
      p[x] = root;
      x = tmp;
    }
    return root;
  }

  inline bool setFriend(int x, int y) {
    int rootX = calcRoot(x);
    int rootY = calcRoot(y);
    if (rootX != rootY) {
      p[rootX] += p[rootY];
      p[rootY] = rootX;
      return true;
    } else {
      return false;
    }
  }

  inline bool isFriend(int x, int y) {
    return calcRoot(x) == calcRoot(y);
  }

  inline int calcSize(int x) {
    return -p[calcRoot(x)];
  }
}; // class DisjointSet
} // namespace cs
