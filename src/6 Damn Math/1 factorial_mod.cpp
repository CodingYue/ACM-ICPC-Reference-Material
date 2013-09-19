<TeX>
	素数p, $n! = ap^k$时, 返回$a (mod p)$
int modFact(long long n, int p) {
	int res = 1;
	while (n > 0) {
		for (int i = 1, m = n % p; i <= m; ++i) res = (long long) res * i % p;
		if ((n /= p) % 2 > 0) res = p - res;
	}
	return res;
}
