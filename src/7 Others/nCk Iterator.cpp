<TeX>升序枚举C(n,k)的所有组合。</TeX>

for(int comb = (1 << k) - 1;comb < (1 << n);) {
	// do something here...

	{ // next
		int x = comb & -comb;
		int y = comb + x;
		comb = ( (unsigned)((comb & ~y) / x) >> 1 ) | y;
	}
}