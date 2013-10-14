int Level[MaxN], Queue[MaxN];
int LRPair[MaxN], Vis[MaxN], RLPair[MaxN];
int visidx = 0;
vector<int> edges[MaxN];

int dfs(int u) {
	Vis[u] = visidx;
	for (vector<int> :: iterator it = edges[u].begin(); it != edges[u].end(); ++it) {
		int v = *it;
		int w = RLPair[v];
		if(w == -1 || (Vis[w] != visidx && Level[u] < Level[w] && dfs(w))) {
			LRPair[u] = v;
			RLPair[v] = u;
			return true;
		}
	}
	return false;
}

int hopcroftKarp(int n, int m) {
	memset(LRPair,-1,sizeof(LRPair[0])*(n+10));
	memset(RLPair,-1,sizeof(RLPair[0])*(m+10));
	for(int match = 0;;) {
		int qf = 0;
		int qe = 0;
		memset(Level,-1,sizeof(Level[0])*(n+10));
		for(int i = 1;i <= n;i++) {
			if(LRPair[i] == -1) {
				Level[i] = 0;
				Queue[qe++] = i;
			}
		}
		while(qf < qe) {
			int u = Queue[qf++];

			for (vector<int> :: iterator it = edges[u].begin(); it != edges[u].end(); ++it) {
				int v = *it;
				int rev = RLPair[v];
				if(rev != -1 && Level[rev] < 0) {
					Level[rev] = Level[u] + 1;
					Queue[qe++] = rev;
				}
			}
		}
		visidx++;
		int d = 0;
		for(int i = 1;i <= n;i++) if(LRPair[i] == -1 && dfs(i)) d++;
		if(d == 0) return match;
		match += d;
	}
	return -1;
}
