ull G[MAXN]; int ans = 0; int plan[MAXN]; int cur[MAXN]; int dp[MAXN];
bool dfs(ull adj,int curClique) {
	if(!adj && curClique > ans) { ans = curClique; return true; } // cur holds an plan
	if(!adj) return false;
	int quota = __builtin_popcountll(adj) + curClique - ans;
	ull enumAdj = adj;
	for(int t = 0;t < quota && enumAdj;t++) {
		int i = __builtin_ctzll(enumAdj);
		if(curClique + dp[i] <= ans) return false;
		//cur[curClique] = i;
		if(dfs(adj & (~((1ull << (i+1)) - 1)) & G[i], curClique+1)) return true;
		enumAdj ^= 1ull << i;
	}
	return false;
}

int maximumClique(int n) {
	ans = 0; memset(dp,0,sizeof(dp));
	
	for(int i = n-1;i >= 0;i--) {
		//cur[0] = i;
		dfs(G[i] & ~((1ull << (i+1)) - 1),1);
		dp[i] = ans;
	}
	return ans;
}
