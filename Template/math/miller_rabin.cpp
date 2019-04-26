/***********************************************************************************************************************
 * TO BE VERIFY
 **********************************************************************************************************************/
namespace math {

namespace {

const int MAXPRIME = 12;
const ULL PRIME[MAXPRIME] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline ULL fix(ULL a, ULL mod) {
  if (a < mod) return a;
  a -= mod;
  if (a < mod) return a;
  return a % mod;
}

inline ULL add(ULL a, ULL b, ULL mod) {
  a += b;
  return a >= mod ? a - mod : a;
}

inline ULL product(ULL a, ULL b, ULL mod) {
	ULL res = 0LL;
	for (a = fix(a, mod); b; b >>= 1) {
		if (b & 1) res = add(res, a, mod);
    a = add(a, a, mod);
	}
	return res;
}

inline ULL exp(ULL a, ULL b, ULL mod) {
	ULL res = 1LL;
	for (a = fix(a, mod); b; b >>= 1) {
		if (b & 1LL) res = product(res, a, mod);
		a = product(a, a, mod);
	}
	return res;
}

} // namespace

inline bool isPrimeMillerRabin(ULL n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (!(n & 1)) return false;
	int k = 0;
  ULL m = n - 1;
	for ( ; !(m & 1); m >>= 1, ++k) {}
	for (int i = 0; i < MAXPRIME; ++i) {
		if (PRIME[i] >= n) return true;
		ULL a = exp(PRIME[i], m, n);
		if (a == 1) continue;
		int j = 0;
		for ( ; j < k; ++j) {
			if (a == n - 1) break;
			a = product(a, a, n);
		}
		if (j < k) continue;
		return false;
	}
	return true;
}
} // namespace math

