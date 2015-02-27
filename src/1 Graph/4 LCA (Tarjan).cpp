<TeX>$O(n)$ 仅在需要顺手维护点别的东西的时候用。</TeX>
void tarjan_lca(int x) {
	ufs[x] = x; vis[x] = true;
	for(QLINK* i = QLink[x];i != NULL;i = i->Next) {
		int qx = i->q->x; int qy = i->q->y;
		if(qx == x && vis[qy]) i->q->lca = ufs_find(qy);
		if(qy == x && vis[qx]) i->q->lca = ufs_find(qx);
	}
	for(EDGE* e = E[x];e;e = e->Next) if(e->y != fa[x]) tarjan_lca(e->y);
	ufs[x] = fa[x];
}
