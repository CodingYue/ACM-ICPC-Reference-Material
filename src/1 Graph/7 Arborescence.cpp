<TeX>最小树形图，注意对 EPool 的需求是 $|V| \times |E|$ 的。
不定根的情况，造一个虚拟根， MAXINT 连上所有的点，最后答案减去 MAXINT 。
求有向森林的同上，插0边即可。可以支持负边权求最大。</TeX>
bool arborescence(int n,int root,double& ans) {
	ans = 0;
	while(1) {
		double minIn[MAXN] = {0};
		int prev[MAXN] = {0};
		fill(minIn,minIn+n,MAXW);
		for(int i = 0;i < n;i++) {
			for(EDGE* e = E[i];e;e = e->Next) {
				int y = e->y;
				if(e->w < minIn[y]) {
					minIn[y] = e->w;
					prev[y] = i;
				}
			}
		}
		for(int i = 0;i < n;i++) {
			for(EDGE* e = E[i];e;e = e->Next) {
				int y = e->y;
				if(y == root) continue;
				e->w -= minIn[e->y];
			}

			if(i == root) continue;
			if(minIn[i] == MAXW) return false; // does not exist
			ans += minIn[i];
		}
		int SCC[MAXN] = {0};
		int vis[MAXN] = {0};
		prev[root] = root;
		int sccidx = 0; int vidx = 0;
		for(int i = 0;i < n;i++) {
			if(vis[i]) continue;
			int x = i; vidx++;
			while(!vis[x]) {
				vis[x] = vidx;
				SCC[x] = sccidx++;
				x = prev[x];
			}
			if(vis[x] == vidx) { // circle
				int ori = x;
				sccidx = SCC[x]+1;
				do {
					SCC[x] = SCC[ori];
					x = prev[x];
				} while(x != ori);
			}
		}
		if(sccidx == n) break; // found
		// rebuild
		EDGE* TE[MAXN] = {0};
		for(int i = 0;i < n;i++)
			for(EDGE* e = E[i];e;e = e->Next)
				if(SCC[i] != SCC[e->y]) insert_edge(SCC[i],SCC[e->y],e->w,TE);
		memcpy(E,TE,sizeof(E));

		n = sccidx;
		root = SCC[root];
	}
	return true;
}
