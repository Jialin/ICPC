#include <cstdio>

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    int a, b, r = 1;
    scanf("%d%d", &a, &b);
    a %= 10;
    for (; b > 0; b >>= 1, a = a * a % 10) {
      if (b & 1) {
        r = r * a % 10;
      }
    }
    printf("%d\n", r);
  }
  return 0;
}
