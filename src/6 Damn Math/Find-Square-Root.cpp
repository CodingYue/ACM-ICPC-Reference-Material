<TeX> 
	Tonelli–Shanks algorithm

	Find such $x$ that $x^2 \equiv n \pmod p$
</TeX>
int find_root(int n, int p) {
	int Q = p - 1, S = 0;
	for (; Q % 2 == 0; Q >>= 1) ++S;
	if (S == 1) return fpow(n, (p + 1) / 4, p);
	int z;
	while (1) {
		z = 1 + rand() % (p - 1); 
		if (fpow(z, (p - 1) / 2, p) != 1) break;
	}
	int c = fpow(z, Q, p);
	int R = fpow(n, (Q + 1) / 2, p);
	int t = fpow(n, Q, p);
	int m = S;
	while (1) {
		if (t % p == 1) break;
		int i = 1;
		for (i = 1; i < m; ++i) if (fpow(t, 1 << i, p) == 1) break;
		int b = fpow(c, 1 << (m - i - 1), p);
		R = (LL) R * b % p;
		t = (LL) t * b % p * b % p;
		c = (LL) b * b % p;
		m = i;
	}
	return (R % p + p) % p;
}

