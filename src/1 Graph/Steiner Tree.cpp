<TeX>求非负无向图上包含ts中所有点的最小Steiner树。G是邻接矩阵。dp[S][v]表示包含S中的点和v的最小Steiner树。 $ O(3^tn+2^tn^2+n^3) $</TeX>

int dp[1 << MAX_M][MAX_N]; // no memset needed
int steiner(int n, vector<int> ts)
{
	int m = ts.size();
	if(m < 2) return 0;

	for(int k = 0;k < n;k++) // Floyd-Warshall
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
				G[i][j] = min(G[i][j],G[i][k] + G[k][j]);

	for(int i = 0;i < m;i++)
		for(int j = 0;j < n;j++)
			dp[1 << i][j] = G[ts[i]][j];
	
	for(int i = 1;i < (1 << m);i++) if( ((i-1) & i) != 0 ) {
		for(int j = 0;j < n;j++) {
			dp[i][j] = INF; // 0x3F3F3F3F or something like.
			for(int k = (i-1) & i;k > 0;k = (k-1) & i)
				dp[i][j] = min(dp[i][j], dp[k][j] + dp[i^k][j]);
		}
		for(int j = 0;j < n;j++)
			for(int k = 0;k < n;k++)
				dp[i][j] = min(dp[i][j], dp[i][k] + G[k][j]);
	}
	return dp[(1<<m) - 1][ts[0]];
}
