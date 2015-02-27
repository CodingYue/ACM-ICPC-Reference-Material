<TeX>$O(n)$ 仅在需要顺手维护点别的东西的时候用。</TeX>
bool vis[40000] = {0};
int djs[40000] = {0};
int djs_find(int x) { return (djs[x] == x ? x : djs[x] = djs_find(djs[x])); }

int tarjan_lca(int root) {
	djs[root] = root;
	vis[root] = true;

	for(QLINK* i = QLink[root];i != NULL;i = i->Next) {
		int qx = i->q->x;
		int qy = i->q->y;
		if(qx == root && vis[qy]) i->q->lca = djs_find(qy);
		if(qy == root && vis[qx]) i->q->lca = djs_find(qx);
	}

	for(EDGE* i = E[root];i != NULL;i = i->Next) {
		int y = i->y;
		if(y == fa[root]) continue;
		
		tarjan_lca(y);
	}
	djs[root] = fa[root];
	return 0;
}
