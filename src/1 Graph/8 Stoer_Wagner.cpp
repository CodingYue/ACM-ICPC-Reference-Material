<TeX>无向图全局最小割。调用前建立邻接矩阵G，跑完后会破坏G。可记录点集。$O(n^3)$ </TeX>
int Stoer_Wagner(int n) {
	int mincut = 0x7FFFFFFF;
	int id[MAXN] = {0};
	int b[MAXN] = {0};
	for(int i = 0;i < n;i++) id[i] = i;
	for(;n > 1;n--) {
		memset(b,0,sizeof(b));
		for(int i = 0;i < n-1;i++) {
			int p = i+1;
			for(int j = i+1;j < n;j++) {
				b[id[j]] += G[id[i]][id[j]];
				if(b[id[p]] < b[id[j]]) p = j;
			}
			swap(id[i+1],id[p]);
		}
		if(b[id[n-1]] < mincut) {
			// ufs_union(st.first,st.second);
			mincut = b[id[n-1]];
			// st = pii(id[n-1],id[n-2]);
		}
		//else ufs_union(id[n-1],id[n-2]);
		for(int i = 0;i < n-2;i++) {
			G[id[i]][id[n-2]] += G[id[i]][id[n-1]];
			G[id[n-2]][id[i]] += G[id[n-1]][id[i]];
		}
	}
	return mincut;
}
