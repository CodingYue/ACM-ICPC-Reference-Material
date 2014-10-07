<TeX>最大团，复杂度上限大概是 $ O(n^{\frac{n}{3}}) $ 左右。G是邻接矩阵，$dp_i$表示由$i$到$n-1$的子图构成的最大团点数，剪枝用。adj中存放的是与i邻接且标号比i大的顶点。

顺便可以保证方案的字典序最小。对adj进行压位有非常良好的效果。</TeX>
const int MAXN = 55;
int G[MAXN][MAXN];

int ans = 0;
int plan[MAXN]; int cur[MAXN]; int dp[MAXN];
bool dfs(int* adj,int adjCnt,int curClique) {
	int nextAdj[MAXN];
	if(!adjCnt) {
		if(curClique > ans) {
			ans = curClique;
			memcpy(plan,cur,sizeof(plan[0])*ans);
			return true;
		}
		return false;
	}
	for(int i = 0;i < adjCnt;i++) {
		if(curClique + adjCnt - i < ans) return false;
		if(curClique + dp[adj[i]] < ans) return false;
		cur[curClique] = adj[i];
		int nextAdjCnt = 0;
		for(int j = i+1;j < adjCnt;j++)
			if(G[adj[i]][adj[j]]) nextAdj[nextAdjCnt++] = adj[j];
		if(dfs(nextAdj,nextAdjCnt,curClique+1)) return true;
	}
	return false;
}

int maximumClique(int n) {
	ans = 0; memset(dp,0,sizeof(dp));

	int adj[MAXN];
	for(int i = n-1;i >= 0;i--) {
		cur[0] = i;
		int adjCnt = 0;
		for(int j = i+1;j < n;j++) if(G[i][j]) adj[adjCnt++] = j;
		dfs(adj,adjCnt,1);
		dp[i] = ans;
	}
	return ans;
}