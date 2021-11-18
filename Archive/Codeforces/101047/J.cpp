// First batch includes
#include "common/include.h"
#include "common/macros.h"
#include "debug/debug_declare.h"

#include "io/read_char_array.h"
#include "io/read_int.h"

// Last include
#include "debug/debug.h"

const int MAXN = 3000 + 1;

char s1[MAXN], s2[MAXN];
vector<double> dp, prevDP;
vector<double> sumDP, prevSumDP;

int main() {
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, m, k;
    io::readInt(n);
    io::readInt(m);
    io::readInt(k);
    io::readCharArray(s1);
    io::readCharArray(s2);
    reverse(s1, s1 + n);
    reverse(s2, s2 + m);
    dp.resize(m + 1);
    sumDP.resize(m + 1);
    dp[0] = 0;
    sumDP[0] = 0;
    FOR(j, 1, m + 1) {
      // 3 & 4
      dp[j] = min(dp[j - 1] + 1, sumDP[j - 1] / j + k);
      sumDP[j] = sumDP[j - 1] + dp[j];
    }
    prevDP.resize(m + 1);
    prevSumDP.resize(m + 1);
    FOR(i, 1, n + 1) {
      prevDP.swap(dp);
      prevSumDP.swap(sumDP);
      // 2 & 4
      dp[0] = min(prevDP[0] + 1, prevSumDP[0] / i + k);
      double rowSum = dp[0];
      sumDP[0] = prevSumDP[0] + rowSum;
      FOR(j, 1, m + 1) {
        if (s1[i - 1] == s2[j - 1]) {
          // 1
          dp[j] = prevDP[j - 1];
        } else {
          // 2 & 3 & 4
          dp[j] = min(min(prevDP[j], dp[j - 1]) + 1, prevSumDP[j - 1] / i / j + k);
        }
        rowSum += dp[j];
        sumDP[j] = prevSumDP[j] + rowSum;
      }
    }
    printf("%.16lf\n", dp[m]);
  }
  return 0;
}
