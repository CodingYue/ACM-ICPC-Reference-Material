<TeX>树分治的大体框架，没整理成模板，起个Hint作用吧。</TeX>

bool disabled[222222];

// init mintree with MAXINT plz...
int mintree = 0;
int cog = -1;
int allSize = 0;
int TreeSize[222222];
int findcog(int x,int fa) {
	TreeSize[x] = 1;
	
	int cur = 0;
	for(EDGE* e = E[x];e;e = e->Next) {
		int y = e->y;
		if(y == fa || disabled[y]) continue;
		findcog(y,x);
		TreeSize[x] += TreeSize[y];
		cur = max(cur,TreeSize[y]);
	}
	cur = max(cur,allSize-TreeSize[x]);
	if(cur < mintree) { mintree = cur; cog = x; }
	return 0;
}

int FuckTree(int root,int size) {
	mintree = 0x7FFFFFFF; cog = -1;
	allSize = size; findcog(root,-1);
	root = cog;
	
	pcnt = 0; // deal subtree ops here
	for(EDGE* e = E[root];e;e = e->Next) {
		int y = e->y;
		int w = e->w;
		if(disabled[y]) continue;
		
		length[y] = w;
		depth[y] = 1;
		dfs(y,y,root); 
	}

	disabled[root] = true;
	for(EDGE* e = E[root];e;e = e->Next) {
		int y = e->y;
		if(disabled[y]) continue;
		
		FuckTree(y,TreeSize[y]);
	}
	return 0;
}
