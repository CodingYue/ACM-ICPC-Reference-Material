<TeX>
returns $1$ if feasible, $0$ if not feasible, $-1$ if unbounded

solutions in $b$

returns $max(cx | Ax <= b)$

$c = A_{m,i}$ 

$b = A_{i,n}$

$A_{m,n}=0$
</TeX>
void pivot(int m, int n, double a[][MaxN], int B[], int N[], int r, int c) {
	swap(N[c], B[r]);
	a[r][c]=1/a[r][c];
	for (int j=0; j<=n; j++)if (j!=c) a[r][j]*=a[r][c];
	for (int i=0; i<=m; i++)if (i!=r) {
		for (int j=0; j<=n; j++)if (j!=c)
			a[i][j]-=a[i][c]*a[r][j];
		a[i][c] = -a[i][c]*a[r][c];
	}
}
int feasible(int m, int n, double a[][MaxN], int B[], int N[]) {
	int r, c; double v;
	while (1) {
		double p = 1e100;
		for (int i=0; i<m; i++) if (a[i][n]<p) p=a[r=i][n];
		if (p>-eps) return 1;
		p = 0;
		for (int i=0; i<n; i++) if (a[r][i]<p) p=a[r][c=i];
		if (p>-eps) return 0;
		p = a[r][n]/a[r][c];
		for (int i=r+1; i<m; i++) if (a[i][c]>eps) {
			v = a[i][n]/a[i][c];
			if (v<p) r=i, p=v;
		}
		pivot(m, n, a, B, N, r, c);
	}
}
int B[10], N[MaxN];
int simplex(int m, int n, double a[][MaxN], double b[], double& ret) {
	int r, c; double v;
	for (int i=0; i<n; i++) N[i]=i;
	for (int i=0; i<m; i++) B[i]=n+i;
	if (!feasible(m, n, a, B, N)) return 0;
	while (1) {
		double p = 0;
		for (int i=0; i<n; i++) if (a[m][i]>p)
			p=a[m][c=i];
		if (p<eps) {
			for (int i=0; i<n; i++) if (N[i]<n)
				b[N[i]]=0;
			for (int i=0; i<m; i++) if (B[i]<n)
				b[B[i]]=a[i][n];
			ret = -a[m][n];
			return 1;
		}
		p = 1e100;
		for (int i=0; i<m; i++) if (a[i][c]>eps) {
			v = a[i][n]/a[i][c];
			if (v<p) p=v, r=i;
		}
		if (p > 1e90) return -1;
		pivot(m, n, a, B, N, r, c);
	}
}
