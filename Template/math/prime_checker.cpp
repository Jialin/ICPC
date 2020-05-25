#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

/**************
 * UNIT TESTS *
 *************/
namespace math {

class PrimeChecker {
public:
  inline PrimeChecker(int n) {
    n_ = n;
    isPrime_.resize(n + 1);
    fill(isPrime_.begin(), isPrime_.end(), true);
    isPrime_[0] = isPrime_[1] = false;
    for (int i = 4; i <= n; i += 2) {
      isPrime_[i] = false;
    }
    for (int i = 3; i <= n && i <= n / i; ++i) {
      if (isPrime_[i]) {
        for (int j = i * i; j <= n; j += i << 1) {
          isPrime_[j] = false;
        }
      }
    }
  }

  inline bool isPrime(int x) {
    assert(x <= n_);
    return x >= 0 ? isPrime_[x] : false;
  }

private:
  int n_;
  vector<bool> isPrime_;
};

} // namespace math
