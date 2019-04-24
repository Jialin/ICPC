namespace gs {

template<typename W>
class EdgeWeightedGraph {
public:
  int n;
  vector<int> lastOut, outDegree;

  vector<int> nxtOut, fromIdx, toIdx;
  vector<W> weights;

  inline int edgeCnt() {
    return static_cast<int>(toIdx.size());
  }

  inline void init(int _n) {
    this->n = _n;
    lastOut.resize(n); fill(lastOut.begin(), lastOut.end(), -1);
    outDegree.resize(n); fill(outDegree.begin(), outDegree.end(), 0);
    nxtOut.clear();
    fromIdx.clear();
    toIdx.clear();
    weights.clear();
  }

  inline void addDirected(int x, int y, const W& w) {
    int edgeIdx = static_cast<int>(nxtOut.size());
    nxtOut.push_back(lastOut[x]);
    fromIdx.push_back(x);
    toIdx.push_back(y);
    weights.push_back(w);
    lastOut[x] = edgeIdx;
    ++outDegree[x];
  }

  inline void addUndirected(int x, int y, const W& w) {
    addDirected(x, y, w);
    addDirected(y, x, w);
  }

  inline string toDisplay() {
    ostringstream ss;
    for (int u = 0; u < n; ++u) {
      ss << u << ':';
      for (int edgeIdx = lastOut[u]; edgeIdx >= 0; edgeIdx = nxtOut[edgeIdx]) {
        ss << ' ' << toIdx[edgeIdx];
      }
      ss << endl;
    }
    return ss.str();
  }
}; // class EdgeWeightedGraph
} // namespace gs

namespace cs {

template<typename T>
class RMQ {
  int n;
  T* vs;
  vector<vector<int>> rmqIdx;

  static inline int highestBit(int n) {
    return 31 - __builtin_clz(n);
  }

  inline void _init() {
    int bit = highestBit(n);
    rmqIdx.resize(bit + 1);
    for (int i = 0; i <= bit; ++i) rmqIdx[i].resize(n - (1 << i) + 1);
    for (int i = 0; i < n; ++i) rmqIdx[0][i] = i;
    for (int i = 1; i <= bit; ++i) for (int j = n - (1 << i), k = j + (1 << (i - 1)); j >= 0; --j, --k) {
      int jIdx = rmqIdx[i - 1][j];
      int kIdx = rmqIdx[i - 1][k];
      rmqIdx[i][j] = vs[jIdx] < vs[kIdx] ? jIdx : kIdx;
    }
  }
public:
  inline void init(int _n, T* _vs) {
    n = _n;
    vs = _vs;
    _init();
  }

  inline void init(vector<T>& _vs) {
    init(static_cast<int>(_vs.size()), _vs.data());
  }

  inline int calcMinIdx(int lower, int upper) {
    int bit = highestBit(upper - lower + 1);
    int lowerIdx = rmqIdx[bit][lower];
    int upperIdx = rmqIdx[bit][upper - (1 << bit) + 1];
    return vs[lowerIdx] < vs[upperIdx] ? lowerIdx : upperIdx;
  }

  inline T& calcMin(int lower, int upper) {
    return vs[calcMinIdx(lower, upper)];
  }
}; // class RMQ
} // namespace cs

namespace trees {

template<typename G>
class LCA {
  vector<int> nodeIdx;
  vector<int> in, out;

  G* tree;
  cs::RMQ<int> depthRMQ;

  inline void dfs(int _depth, int u, int parent) {
    in[u] = static_cast<int>(depth.size());
    out[u] = in[u];
    depth.push_back(_depth);
    nodeIdx.push_back(u);
    for (int edgeIdx = tree->lastOut[u]; edgeIdx >= 0; edgeIdx = tree->nxtOut[edgeIdx]) {
      int v = tree->toIdx[edgeIdx];
      if (v == parent) continue;
      dfs(_depth + 1, v, u);
      out[u] = static_cast<int>(depth.size());
      depth.push_back(_depth);
      nodeIdx.push_back(u);
    }
  }
public:
  vector<int> depth;

  inline void init(G& _tree) {
    tree = &_tree;
    int n = tree->n, n3 = n * 3;
    depth.clear(); depth.reserve(n3);
    nodeIdx.clear(); nodeIdx.reserve(n3);
    in.clear(); in.reserve(n);
    out.clear(); out.reserve(n);
    dfs(0, 0, -1);
    depthRMQ.init(depth);
  }

  inline int calc(int x, int y) {
    int idx = depthRMQ.calcMinIdx(min(in[x], in[y]), max(out[x], out[y]));
    return nodeIdx[idx];
  }
}; // class LCA
} // namespace trees

namespace trees {

/**
 * - The first {originalTree.n} components corresponding to the single node components of the original tree;
 * - The next {nodeCnt-originalTree.n} components corresponding to the single node components which was added in order
 *   to ensure all nodes has degree <= 3;
 * - The next {compCnt-nodeCnt} components corresponding to non-single node components.
 * - # components <= # nodes in the original tree * 4
 *
 * NOTE: the first nodeCnt components will corresponding to the single node component according to the node in the
 * original tree.
 */
template<typename W>
class DivideConquerEdgeDecomposor {
  gs::EdgeWeightedGraph<W>* originalTree;
  queue<int> childrenQ;
  queue<W> weightQ;
  trees::LCA<gs::EdgeWeightedGraph<W>> lca;

  // Structure of componenents in the divide and conquer decomposition
  gs::EdgeWeightedGraph<W> transformedTree;

  template<typename T>
  inline void clearQ(queue<T> &q) {
    for ( ; !q.empty(); q.pop()) {}
  }

  inline int popChildren() {
    int res = childrenQ.front();
    childrenQ.pop();
    return res;
  }

  inline int popWeight() {
    if (weightQ.empty()) return 0;
    int res = weightQ.front();
    weightQ.pop();
    return res;
  }

  inline void buildTree(int u, int _parent) {
    clearQ(childrenQ);
    clearQ(weightQ);
    for (int edgeIdx = originalTree->lastOut[u]; edgeIdx >= 0; edgeIdx = originalTree->nxtOut[edgeIdx]) {
      int v = originalTree->toIdx[edgeIdx];
      if (v == _parent) continue;
      childrenQ.push(v);
      weightQ.push(originalTree->weights[edgeIdx]);
    }
    while (childrenQ.size() > 2) {
      transformedTree.addUndirected(popChildren(), nodeCnt, popWeight());
      transformedTree.addUndirected(popChildren(), nodeCnt, popWeight());
      childrenQ.push(nodeCnt++);
    }
    while (!childrenQ.empty()) transformedTree.addUndirected(popChildren(), u, popWeight());
    for (int edgeIdx = originalTree->lastOut[u]; edgeIdx >= 0; edgeIdx = originalTree->nxtOut[edgeIdx]) {
      int v = originalTree->toIdx[edgeIdx];
      if (v == _parent) continue;
      buildTree(v, u);
    }
  }

  vector<bool> edgeBlocked;
  vector<int> subSizes;

  inline int dfsSizes(int u, int _parent) {
    int& res = subSizes[u];
    res = 1;
    for (int edgeIdx = transformedTree.lastOut[u]; edgeIdx >= 0; edgeIdx = transformedTree.nxtOut[edgeIdx]) if (!edgeBlocked[edgeIdx]) {
      int v = transformedTree.toIdx[edgeIdx];
      if (v == _parent) continue;
      res += dfsSizes(v, u);
    }
    return res;
  }

  int resDelta, resEdgeIdx;

  inline void dfsCut(int u, int _parent, int totalSize) {
    for (int edgeIdx = transformedTree.lastOut[u]; edgeIdx >= 0; edgeIdx = transformedTree.nxtOut[edgeIdx]) if (!edgeBlocked[edgeIdx]) {
      int v = transformedTree.toIdx[edgeIdx];
      if (v == _parent) continue;
      int subResDelta = abs(totalSize - (subSizes[v] << 1));
      if (resEdgeIdx < 0 || subResDelta < resDelta) {
        resEdgeIdx = edgeIdx;
        resDelta = subResDelta;
      }
      dfsCut(v, u, totalSize);
    }
  }

  queue<int> dfsQ, compQ;

  inline void decompose() {
    int pnt = (nodeCnt << 1) - 2;
    clearQ(dfsQ); dfsQ.push(0);
    clearQ(compQ); compQ.push(pnt--);
    for ( ; !dfsQ.empty(); dfsQ.pop(), compQ.pop()) {
      int u = dfsQ.front();
      int compIdx = compQ.front();
      roots[compIdx] = u;
      dfsSizes(u, -1);
      resEdgeIdx = -1;
      dfsCut(u, -1, subSizes[u]);
      cutEdge[compIdx] = resEdgeIdx;
      int x = transformedTree.fromIdx[resEdgeIdx];
      int y = transformedTree.toIdx[resEdgeIdx];
      int sizeY = subSizes[y], sizeX = subSizes[u] - sizeY;
      edgeBlocked[resEdgeIdx] = edgeBlocked[resEdgeIdx ^ 1] = true;
      int leftCompIdx = x;
      if (sizeX > 1) {
        leftCompIdx = pnt;
        dfsQ.push(x);
        compQ.push(pnt--);
      }
      int rightCompIdx = y;
      if (sizeY > 1) {
        rightCompIdx = pnt;
        dfsQ.push(y);
        compQ.push(pnt--);
      }
      leftChild[compIdx] = leftCompIdx; parent[leftCompIdx] = compIdx;
      rightChild[compIdx] = rightCompIdx; parent[rightCompIdx] = compIdx;
    }
  }

  inline void dfs(int u, int _parent, W _pathSum) {
    pathSum[u] = _pathSum;
    for (int edgeIdx = transformedTree.lastOut[u]; edgeIdx >= 0; edgeIdx = transformedTree.nxtOut[edgeIdx]) {
      int v = transformedTree.toIdx[edgeIdx];
      if (v == _parent) continue;
      dfs(v, u, _pathSum + transformedTree.weights[edgeIdx]);
    }
  }

  inline int calcNewNodeCnt() {
    int res = 0;
    for (int i = 0; i < originalTree->n; ++i) {
      res += max(originalTree->outDegree[i] - (i > 0) - 2, 0);
    }
    return res;
  }
public:
  // Component count
  int compCnt;
  // Parent component ID
  vector<int> parent;
  // Left and right component ID
  vector<int> leftChild, rightChild;
  // Edge index in the transformed tree divides the component
  vector<int> cutEdge;
  // Root node index in the transformed tree of the component
  vector<int> roots;

  // Number of nodes in transfomred tree
  int nodeCnt;
  // Path sum from the node to root in transformed tree
  vector<W> pathSum;

  // Decomposes the tree
  inline void calc(gs::EdgeWeightedGraph<W>& _originalTree) {
    // build tree
    int n = _originalTree.n;
    originalTree = &_originalTree;
    nodeCnt = n;
    transformedTree.init(n + calcNewNodeCnt());
    buildTree(0, -1);
    // divide and conquer decomposition
    edgeBlocked.resize(transformedTree.edgeCnt()); fill(edgeBlocked.begin(), edgeBlocked.end(), false);
    subSizes.resize(nodeCnt);
    compCnt = (nodeCnt << 1) - 1;
    parent.resize(compCnt); parent[compCnt - 1] = -1;
    leftChild.resize(compCnt);
    rightChild.resize(compCnt);
    cutEdge.resize(compCnt);
    roots.resize(compCnt);
    pathSum.resize(nodeCnt);
    for (int i = 0; i < nodeCnt; ++i) {
      leftChild[i] = rightChild[i] = cutEdge[i] = -1;
      roots[i] = i;
    }
    decompose();
    dfs(0, -1, 0);
    lca.init(transformedTree);
  }

  // Sibling component
  inline int sibling(int u) {
    int uParent = parent[u];
    if (uParent < 0) return -1;
    return leftChild[uParent] == u ? rightChild[uParent] : leftChild[uParent];
  }

  // Depth of the node in transformed tree
  inline int depth(int u) {
    return lca.depth[u];
  }

  // Edge weight in the transfomred tree divides the component
  inline W cutEdgeWeight(int u) {
    return transformedTree.weights[cutEdge[u]];
  }

  // Caculates the path from u to v.
  inline W calcPath(int u, int v) {
    W& pathRoot = pathSum[lca.calc(u, v)];
    return (pathSum[u] - pathRoot) + (pathSum[v] - pathRoot);
  }
}; // class DivideConquerEdgeDecomposor
} // namespace trees

/***********************************************************************************************************************
 * Testing
 **********************************************************************************************************************/
namespace testing {

template<typename W>
string display(trees::DivideConquerEdgeDecomposor<W>& de) {
  ostringstream ss;
  ss << "nodeCnt: " << de.nodeCnt << endl;
  ss << "compCnt: " << de.compCnt << endl;
  for (int i = de.compCnt - 1; i >= 0; --i) {
    ss << "comp@" << i << ": ";
    ss << "root(" << de.roots[i] << ") ";
    if (i >= de.nodeCnt) {
      ss << "cutEdgeWight(" << de.cutEdgeWeight(i) << ") ";
      ss << "childComp(" << de.leftChild[i] << ',' << de.rightChild[i] << ")";
    }
    ss << endl;
  }
  return ss.str();
}
} // namespace testing

/***********************************************************************************************************************
 * Example(QTREE4):
 *   # weighted tree
 *   # flip the color of a given node (white / black)
 *   # find the farest white nodes pairs
 **********************************************************************************************************************/
void cleanUp(priority_queue<pair<int, int>>& q) {
  for ( ; !q.empty() && !white[q.top().second]; q.pop()) {}
}

void update(int u) {
  white[u] = !white[u];
  for (int i = u; i >= 0; i = de.parent[i]) {
    auto& q = heap[i];
    cleanUp(q);
    if (white[u] && (q.empty() || q.top().second != u)) {
      q.emplace(de.calcPath(u, de.roots[i]), u);
    }
    if (i < de.nodeCnt) {
      bestPath[i] = white[u] ? 0 : -INF;
    } else {
      int& res = bestPath[i];
      int l = de.leftChild[i], r = de.rightChild[i];
      res = max(bestPath[l], bestPath[r]);
      if (!heap[l].empty() && !heap[r].empty()) {
        res = max(res, heap[l].top().first + de.cutEdgeWeight(i) + heap[r].top().first);
      }
    }
  }
}

/***********************************************************************************************************************
 * Example(QTREE5):
 *   # unweighted tree
 *   # flip the color of a given node (white / black)
 *   # find the closest white nodes to a given node
 **********************************************************************************************************************/
void cleanUp(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& q) {
  for ( ; !q.empty() && !white[q.top().second]; q.pop()) {}
}

void update(int u) {
  white[u] = !white[u];
  if (!white[u]) return;
  for (int i = u; i >= 0; i = de.parent[i]) {
    auto& q = heap[i];
    cleanUp(q);
    if (q.empty() || q.top().second != u) {
      q.emplace(de.calcPath(u, de.roots[i]), u);
    }
  }
}

int calc(int u) {
  if (white[u]) return 0;
  int res = INF;
  for (int i = u; i >= 0; i = de.parent[i]) {
    int j = de.sibling(i);
    if (j < 0) break;
    auto& q = heap[j];
    cleanUp(q);
    if (heap[j].empty()) continue;
    res = min(res, de.calcPath(u, de.roots[i]) + de.cutEdgeWeight(de.parent[i]) + q.top().first);
  }
  return res == INF ? -1 : res;
}

