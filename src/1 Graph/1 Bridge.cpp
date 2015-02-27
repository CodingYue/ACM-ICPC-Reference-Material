<TeX>无向图求桥，支持重边。直接拆掉桥就是边BCC。</TeX>
int DFN[MAXN],Low[MAXN];
bool vis[MAXN],isBridge[MAXM];
int idx = 0;
int tarjan(int x,int peid=-1) {
	vis[x] = true;
	DFN[x] = Low[x] = ++idx;
	for(EDGE* e = E[x];e;e = e->Next) {
		int y = e->y; int eid = e->id;
		if(eid == peid) continue;
		if(!vis[y]) {
			tarjan(y,eid);
			Low[x] = min(Low[x],Low[y]);
		}
		else Low[x] = min(Low[x],DFN[y]);
	}
	if(peid != -1 && Low[x] == DFN[x]) isBridge[peid] = true;
	return 0;
}
