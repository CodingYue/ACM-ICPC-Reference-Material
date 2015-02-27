<TeX> 倍增LCA $O(n\log n)$ 只要维护的是树，可以动态添加 </TeX>
int fa[111111][18];
int depth[111111];
int lca(int x,int y) {
	if(depth[x] < depth[y]) swap(x,y);
	int delta = depth[x]-depth[y];
	for(int i = 0;i < 16;i++) if(delta&(1<<i)) x = fa[x][i];
	for(int i = 15;i >= 0;i--) if(fa[x][i] != fa[y][i]) { x = fa[x][i]; y = fa[y][i]; }
	if(x != y) x = fa[x][0];
	return x;
}