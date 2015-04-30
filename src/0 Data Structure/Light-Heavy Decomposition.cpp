<TeX> 递归版本， NodeID 为全局ID，保证了dfs序。如果需要非递归版本，先写bfs算好fa/Depth/TreeSize/HeavyChild，然后抄下面Hint部分。</TeX>
int BlockRoot[MAXN], NodeID[MAXN], IndexToNode[MAXN], TreeSize[MAXN], Depth[MAXN], fa[MAXN];
int NodeID_Out[MAXN]; // 离开节点的时候的dfs序
int HeavyChild[MAXN]; // 0 if not set
int idx = 0;
int dfs_size(int x) {
	TreeSize[x] = 1;
	for(EDGE* e = E[x];e;e = e->Next) {
		int y = e->y;
		if(y == fa[x]) continue;

		fa[y] = x; Depth[y] = Depth[x]+1;
		dfs_size(y);
		TreeSize[x] += TreeSize[y];
		if(TreeSize[HeavyChild[x]] < TreeSize[y]) HeavyChild[x] = y;
	}
	return 0;
}
int dfs_lh(int x,int block) {
	BlockRoot[x] = block; NodeID[x] = ++idx; IndexToNode[idx] = x;
	if(HeavyChild[x]) dfs_lh(HeavyChild[x],block);
	for(EDGE* e = E[x];e;e = e->Next) {
		int y = e->y;
		if(y == fa[x] || y == HeavyChild[x]) continue;
		dfs_lh(y,y);
	}
	NodeID_Out[x] = idx;
	return 0;
}
int Decomposition(int s,int N) {
	idx = 0; fa[s] = 0;
	memset(HeavyChild,0,sizeof(HeavyChild[0])*(N+10));
	dfs_size(s); dfs_lh(s,s);
	return 0;
}

// 如果需要非递归的，一点提示，bfs都会写，后面的：
for(int i = qend-1;i >= 0;i--) {
	int x = Queue[i];
	if(x == HeavyChild[fa[x]]) continue;
	int t = x;
	while(t) {
		BlockRoot[t] = x;
		NodeID[t] = ++idx;
		t = HeavyChild[t];
	}
}

// 参考用爬树过程
int ColorNode(int x,int y,int nc) {
	while(1) {
		if(Depth[BlockRoot[x]] > Depth[BlockRoot[y]]) swap(x,y);
		 
		if(BlockRoot[x] == BlockRoot[y]) {
			if(Depth[x] > Depth[y]) swap(x,y);
			Seg_Modify(NodeID[x],NodeID[y],nc,1,idx);
			break;
		}
		Seg_Modify(NodeID[BlockRoot[y]],NodeID[y],nc,1,idx);
		y = fa[BlockRoot[y]];
	}
	return 0;
}
