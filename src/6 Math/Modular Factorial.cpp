<TeX>n! % mod where mod = p^k。 $O(p \log n)$</TeX>

LL get(int n, int mod, int p) {
	LL ans = 1;
	for (int i = 1; i <= n; ++i) if (i % p != 0) {
		ans = ans * i % mod;
	}
	return ans;
}
pii solve(LL n, int mod, int p) {
	LL init = get(mod, mod, p);
	pii ans = pii(1, 0);
	for (LL now = p; now <= n; now *= p) {
		ans.second += n / now;
		if (now > n / p) break;
	}
	while (n > 0) {
		ans.first = (LL) ans.first * fpow(init, n / mod, mod) % mod;
		ans.first = ans.first * get(n % mod, mod, p) % mod;
		n /= p;
	}
	return ans;
}
