<TeX>$O(nm+n^2)$ 最大平均权值环 需要存边但是不需要边表。</TeX>
int d[677][677] = {0};
double Karp(int n,int m) {
	memset(d,0,sizeof(d));

	// init all d[0][i] with 0 if no memset or reversing 

	for(int i = 1;i <= n;i++) for(int j = 0;j < m;j++)
		if(d[i][E[j].y] < d[i-1][E[j].x]+E[j].k) d[i][E[j].y] = d[i-1][E[j].x]+E[j].k;
	
	double u = 0.0;
	for(int i = 0;i < n;i++) {
		double t = 1e100;
		for(int j = 0;j < n;j++)
			if(d[j][i] >= 0) {
				double k = (double)(d[n][i]-d[j][i])/(n-j);
				if(k < t) t = k;
			}
		if(t > u) u = t;
	}
	return u;
}
