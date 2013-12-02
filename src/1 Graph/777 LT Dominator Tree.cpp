<TeX>有向图，redge是反向边。最后附有用法说明，idom是输出结果，即每个点的直接dominator点。全部标号0起始。复杂度是$O(N log N)$</TeX>
int fa[MAXN],nodeName[MAXN],nodeID[MAXN]; // ID->Name || Name->ID || ID = dfs order(DFN)
bool vis[MAXN]; int ncnt = 0;
vector<int> edges[MAXN],redges[MAXN];
int dfs(int x)
{
	vis[x] = true;
	nodeID[x] = ncnt; nodeName[ncnt++] = x;
	for(vit it = edges[x].begin();it != edges[x].end();++it)
	{
		if(vis[*it]) continue;
		fa[*it] = x; dfs(*it);
	}
	return 0;
}
int semi[MAXN],idom[MAXN],ufs[MAXN];
int mnsemi[MAXN]; // maintained during ufs_merge
vector<int> bucket[MAXN];

// x -> y
int ufs_union(int x,int y) { ufs[x] = y; return 0; }
int ufs_internal_find(int x)
{
	if(ufs[ufs[x]] == ufs[x]) return 0;
	ufs_internal_find(ufs[x]);
	if(semi[mnsemi[ufs[x]]] < semi[mnsemi[x]]) mnsemi[x] = mnsemi[ufs[x]];
	ufs[x] = ufs[ufs[x]];
	return 0;
}
int ufs_find(int x)
{
	if(ufs[x] == x) return x;
	ufs_internal_find(x);
	return mnsemi[x];
}

int calc_dominator_tree(int n)
{
	for(int i = 0;i < n;i++) { semi[i] = i; mnsemi[i] = i; ufs[i] = i; }
	for(int x = n-1;x > 0;x--)
	{
		int tfa = nodeID[fa[nodeName[x]]];
		for(vit it = redges[nodeName[x]].begin();it != redges[nodeName[x]].end();++it)
		{
			if(!vis[*it]) continue;
			int fy = ufs_find(nodeID[*it]);
			if(semi[fy] < semi[x]) semi[x] = semi[fy];
		}
		bucket[semi[x]].push_back(x);
		ufs_union(x,tfa);

		for(vit it = bucket[tfa].begin();it != bucket[tfa].end();++it)
		{
			int fy = ufs_find(*it);
			idom[nodeName[*it]] = nodeName[semi[fy] < semi[*it] ? fy : tfa];
		}
		bucket[tfa].clear();
	}
	for(int x = 1;x < n;x++)
	{
		if(idom[nodeName[x]] != nodeName[semi[x]])
		{
			idom[nodeName[x]] = idom[idom[nodeName[x]]];
		}
	}
	idom[nodeName[0]] = -1;
	return 0;
}

memset(fa,-1,sizeof(fa[0])*(n+10));
memset(idom,-1,sizeof(idom[0])*(n+10));
memset(vis,0,sizeof(vis[0])*(n+10));
for(int i = 0;i < n;i++) bucket[i].clear();
ncnt = 0;
dfs(n-1); // n-1 is source
calc_dominator_tree(ncnt);
