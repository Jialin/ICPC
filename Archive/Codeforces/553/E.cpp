// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#define COMPLEX_INIT_MUL
#define FORWARD_STAR_EDGE_WEIGHTED_SPFA
#include "graph/forward_star/forward_star_edge_weighted_macros.h"
#include "math/fft/fft_utils_macros.h"

#include "graph/forward_star/forward_star_edge_weighted.h"
#include "io/read_int.h"
#include "math/fft/fft_utils.h"

// Last include
#include "debug/debug.h"

const int MAXN = 50;
const double EPS = 1E-6;

using FFT_T = double;
using Complex = math::Complex<FFT_T>;
using FFTUtils = math::FFTUtils<FFT_T>;

struct Edge {
  int cost;
  vector<Complex> timeCost;
};

graph::ForwardStarEdgeWeighted<Edge> fs;
vector<double> costs[MAXN];
int T, Tp1, Tp2, Tpow2;

int fftOldCostIdx;
vector<Complex> fftOldCost, newCost;

auto spfaUpdater = [](int fromIdx, int toIdx, int edgeIdx) {
  if (fftOldCostIdx != fromIdx) {
    fftOldCostIdx = fromIdx;
    fftOldCost.resize(Tpow2);
    FOR(i, 0, Tpow2) {
      fftOldCost[i].init(costs[fromIdx][min(i, Tp1)], 0);
    }
    FFTUtils::instance().fft(fftOldCost, false);
  }
  const auto& weight = fs.weights[edgeIdx];
  newCost.resize(Tpow2);
  FOR(i, 0, Tpow2) {
    newCost[i].initMul(fftOldCost[i], weight.timeCost[i]);
  }
  FFTUtils::instance().fft(newCost, true);
  auto& targetCosts = costs[toIdx];
  bool updated = false;
  FOR(i, 0, T + 2) {
    if (targetCosts[i] > newCost[i + T].real + weight.cost + EPS) {
      updated = true;
      targetCosts[i] = newCost[i + T].real + weight.cost;
    }
  }
  return updated;
};

int main() {
  int n, m, penalty;
  while (io::readInt(n)) {
    io::readInt(m);
    io::readInt(T);
    Tp1 = T + 1;
    Tp2 = T + 2;
    Tpow2 = math::nextPow2_32((T << 1) + 2);
    io::readInt(penalty);
    fs.init(n, m);
    FOR(i, 0, m) {
      Edge edge;
      int x, y;
      io::readInt(x);
      io::readInt(y);
      io::readInt(edge.cost);
      --x;
      --y;
      auto& timeCost = edge.timeCost;
      timeCost.resize(Tpow2);
      for (int j = T - 1; j >= 0; --j) {
        int v;
        io::readInt(v);
        timeCost[j].init(v / 100000.0, 0);
      }
      FOR(j, T, Tpow2) {
        timeCost[j].init(0, 0);
      }
      FFTUtils::instance().fft(timeCost, false);
      fs.addDirected(y, x, std::move(edge));
    }
    FOR(i, 0, n - 1) {
      costs[i].assign(Tp2, 1E100);
    }
    costs[n - 1].assign(Tp2, 0);
    costs[n - 1][Tp1] = penalty;
    fftOldCostIdx = -1;
    fs.spfa(n - 1, spfaUpdater);
    printf("%.13lf\n", costs[0][0]);
  }
}
