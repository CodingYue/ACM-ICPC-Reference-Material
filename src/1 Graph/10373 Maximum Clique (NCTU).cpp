<TeX>魔法！</TeX>
ULL edge[MXN];
int go(ULL candi, int ans, int szCur) {
	if (candi == 0) return ans;
	if (ans <= szCur) ans = szCur + 1;

	ULL ncandi = candi;
	int quota = __builtin_popcountll(candi) + szCur - ans;
	while (ncandi && --quota >= 0) {
		int i = __builtin_ctzll(ncandi);
		candi ^= (1ULL << i);
		if (ncandi & edge[i]) ans = go(candi & edge[i], ans, szCur + 1);
		ncandi ^= (1ULL << i);
		if (candi == ncandi) ncandi &= ~edge[i];
	}
	return ans;
}
ans = go((1ULL << n) - 1, 0, 0);
