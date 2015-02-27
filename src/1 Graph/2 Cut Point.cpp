<TeX>求割点/点BCC，同样支持重边。BCCId为某条边在哪个BCC内。</TeX>
int DFN[MAXN],Low[MAXN],Stack[MAXM],BCCId[MAXM];
bool vis[MAXN],isCP[MAXN];
int idx = 0,BCCidx = 0,STop = 0;
int tarjan(int x,int peid=-1) {
	vis[x] = true;
	DFN[x] = Low[x] = ++idx;
	int ecnt = 0;
	for(EDGE* e = E[x];e;e = e->Next) {
		int y = e->y; int eid = e->id;
		if(eid == peid) continue;
		if(DFN[y] < DFN[x]) Stack[STop++] = eid;
		if(!vis[y]) {
			tarjan(y,eid);
			Low[x] = min(Low[x],Low[y]);
			ecnt++;
			if(DFN[x] <= Low[y]) {
				BCCidx++;
				while(Stack[--STop] != e->eid) BCCId[Stack[STop]] = BCCidx;
				BCCId[e->eid] = BCCidx;

				if(peid != -1) isCP[x] = true;
			}
		}
		else Low[x] = min(Low[x],DFN[y]);
	}
	if(peid == -1 && ecnt > 1) isCP[x] = true;
	return 0;
}
