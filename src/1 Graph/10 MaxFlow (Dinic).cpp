<TeX>对于一条边，如果他的两个点分属不同的连通分量且满流则这条边可属于网络的最小割。
如果他的两个点分属不同的联通分量且满流且两个点分别和source，sink属于同一个连通分量，则这条边必属于最小割。

	@Yuege: 请，一定，要，用，dfs，找割集。</TeX>
class DinicMaxFlow {
public:
	void reset() { memset(Arc,0,sizeof(Arc)); APTop = APool; }
	DinicMaxFlow() { reset(); }

	int level[MAXN]; int s,t,n;
	bool bfs_level() {
		memset(level,-1,sizeof(level[0]) * (n+3));
		int front(0), end(0);
		static int queue[MAXN];
		queue[end++] = s; level[s] = 0;
		while(front < end) {
			int x = queue[front++];
			for(ARC* ar = Arc[x];ar;ar = ar->Next)
				if(ar->c > 0 && level[ar->y] == -1) {
					level[ar->y] = level[x] + 1;
					queue[end++] = ar->y;
				}
		}
		return level[t] != -1;
	}

	int dfs_augment(int x,int available) {
		if(x == t) return available;
		int used = 0;
		for(ARC* ar = Arc[x];ar && used < available;ar = ar->Next)
			if(ar->c > 0 && level[ar->y] == level[x] + 1) {
				int tflow = dfs_augment(ar->y, min(ar->c, available-used));
				used += tflow;
				ar->c -= tflow; ar->R->c += tflow;
			}
		if(!used) level[x] = -1;
		return used;
	}

	int dinic(int s,int t,int n) {
		this->s = s; this->t = t; this->n = n;
		
		int maxflow(0), tflow(0);
		while(bfs_level()) while((tflow = dfs_augment(s,INF))) maxflow += tflow;
		return maxflow;
	}
};