#pragma once

using namespace std;

namespace algo {

template<typename Args, const int BLOCK>
struct BaseSqrtDeco {
  virtual inline void _handleNode(int idx, Args& args) = 0;
  virtual inline void _handleBlock(int blockIdx, Args& args) = 0;

  inline void handleRange(int lower, int upper, Args& args) {
    int lowerBlock = lower / BLOCK;
    int upperBlock = upper / BLOCK;
    if (lowerBlock == upperBlock) {
      FOR(i, lower, upper) {
        _handleNode(i, args);
      }
    } else {
      int idx;
      idx = lowerBlock * BLOCK;
      if (idx != lower) {
        idx += BLOCK;
        FOR(i, lower, idx) {
          _handleNode(i, args);
        }
      } else {
        _handleBlock(lowerBlock, args);
      }
      FOR(i, lowerBlock + 1, upperBlock) {
        _handleBlock(i, args);
      }
      idx = upperBlock * BLOCK;
      FOR(i, idx, upper) {
        _handleNode(i, args);
      }
    }
  }
};

} // namespace algo
