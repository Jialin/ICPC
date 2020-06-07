#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  printf("%lld\n", (9 * n - 3LL) << ((n - 3) << 1));
  return 0;
}
