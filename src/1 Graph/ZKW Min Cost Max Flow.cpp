<TeX>调用前使用init清空,需要指定src,des和$n$,对应$S$和$T$，$n$为总点数</TeX>
struct EDGE {
	int cost, cap, v;
	int next, re;
}edge[MAXM];
int head[MAXN], e;
int vis[MAXN];
int ans, cost, src, des, n;
void init() {
	memset(head, -1, sizeof(head));
	e = ans = cost = 0;
}
void addedge(int u, int v, int cap, int cost) {
	edge[e].v = v; edge[e].cap = cap;
	edge[e].cost = cost; edge[e].re = e + 1;
	edge[e].next = head[u]; head[u] = e++;

	edge[e].v = u; edge[e].cap = 0;
	edge[e].cost = -cost; edge[e].re = e - 1;
	edge[e].next = head[v]; head[v] = e++;
}
int aug(int u, int f) {
	if(u == des) {
		ans += cost * f;
		return f;
	}
	vis[u] = 1;
	int tmp = f;
	for(int i = head[u]; i != -1; i = edge[i].next) {
		if(edge[i].cap && !edge[i].cost && !vis[edge[i].v]) {
			int delta = aug(edge[i].v, tmp < edge[i].cap ? tmp : edge[i].cap);
			edge[i].cap -= delta; edge[edge[i].re].cap += delta;
			tmp -= delta;
			if(!tmp) return f;
		}
	}
	return f - tmp;
}
bool modlabel() {
	int delta = INF;
	for(int u = 0; u < n; u++) if(vis[u])
		for(int i = head[u]; i != -1; i = edge[i].next)
			if(edge[i].cap && !vis[edge[i].v] && edge[i].cost < delta) delta = edge[i].cost;
	if(delta == INF) return false;
	for(int u = 0; u < n; u++) if(vis[u])
		for(int i = head[u]; i != -1; i = edge[i].next)
			edge[i].cost -= delta, edge[edge[i].re].cost += delta;
	cost += delta;
	return true;
}
void costflow() {
	do do memset(vis, 0, sizeof(vis)); 
	while(aug(src, INF)); while(modlabel());
}
