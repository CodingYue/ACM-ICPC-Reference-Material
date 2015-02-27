<TeX>治疗递推式。对于形如$a_{i+n} = \sum k_ja_{i+j} + d$的递推式，求出其写成$a_m = \sum c_ia_i + c_nd$这一形式时的系数$c_i$。工作在double上，可以比较显然的改成int取模。
代码中$c$为传出的答案，需要自行alloc。

$O(n^2 \log m)$ $k_i$稀疏的话用FFT可以达成$O(n \log n \log m)$</TeX>

// c at least double c[n+1]
int recFormula(double* k, int n, long long m, double* c) {
	memset(c,0,sizeof(*c)*(n+1));
	if(m < n) c[m] = 1;
	else {
		double* b = new double[n+1];
		recFormula(k, n, m >> 1, b);

		static double a[MAXN*2];
		memset(a,0,sizeof(a[0])*(n*2));

		int s = m & 1;
		for(int i = 0;i < n;i++) {
			for(int j = 0;j < n;j++) a[i + j + s] += b[i] * b[j];
			c[n] += b[i];
		}
		c[n] = (c[n] + 1) * b[n];
		for(int i = n * 2 - 1;i >= n;i--) {
			for(int j = 0;j < n;j++) a[i - n + j] += k[j] * a[i];
			c[n] += a[i];
		}
		memcpy(c,a,sizeof(c[0])*n); // c[n] is c[n], do not copy it.
		delete[] b;
	}
	return 0;
}
