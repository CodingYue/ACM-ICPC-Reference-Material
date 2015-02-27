<TeX> 最大流，时间复杂度 $O(n^2m)$ 。多次使用记得初始化。

	对于一条边，如果他的两个点分属不同的连通分量且满流则这条边可属于网络的最小割。
	
	如果他的两个点分属不同的联通分量且满流且两个点分别和source，sink属于同一个连通分量，则这条边必属于最小割。

	@Yuege: 请，一定，要，用，dfs，找割集。
</TeX>
const int MAXM = 1000000;
const int MAXN = 25000;
const int INF = 0x7FFFFFFF;

struct ARC { int y,c; ARC* Next,*R; };
ARC APool[MAXM*2]; ARC* APTop = APool; ARC* Arc[MAXN];

int insert_arc(int x,int y,int c,int rc=0) {
	ARC* fore = APTop++;
	fore->y = y; fore->c = c; fore->Next = Arc[x]; Arc[x] = fore;
	ARC* back = APTop++;
	back->y = x; back->c = rc; back->Next = Arc[y]; Arc[y] = back;

	fore->R = back; back->R = fore;
	return 0;
}

int dis[MAXN],pre[MAXN],gap[MAXN];
ARC* curArc[MAXN];
int init_distance_mark(int s,int t,int n) {
	fill(dis,dis+MAXN,n);
	queue<int> q;
	q.push(t);
	dis[t] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(ARC* a = Arc[x];a;a = a->Next) {
			if(a->R->c <= 0) continue;
			if(dis[a->y] > dis[x]+1) {
				dis[a->y] = dis[x]+1;
				q.push(a->y);
			}
		}
	}
	memset(gap,0,sizeof(gap));
	for(int i = 0;i < n;i++) gap[dis[i]]++;
	return 0;
}
int max_flow(int s,int t,int n) {
	memset(dis,0,sizeof(dis));
	memset(curArc,0,sizeof(curArc));
	// memset(gap,0,sizeof(gap));
	// gap[0] = n;
	init_distance_mark(s,t,n);

	int maxflow = 0;
	int x = s;
	while(dis[s] < n) {
		if(x == t) {
			int tflow = INF;
			for(x = t;x != s;x = pre[x]) tflow = min(tflow,curArc[pre[x]]->c);
			for(x = t;x != s;x = pre[x]) {
				curArc[pre[x]]->c -= tflow;
				curArc[pre[x]]->R->c += tflow;
			}
			maxflow += tflow;
			continue;
		}
		if(!curArc[x]) curArc[x] = Arc[x];
		ARC* ar = curArc[x];
		for(;ar;ar = ar->Next) if(ar->c && dis[ar->y]+1 == dis[x]) break;
		curArc[x] = ar;
		if(!ar) {
			int mindis = n+1; // relabel
			for(ARC* a = Arc[x];a;a = a->Next) if(a->c) mindis = min(mindis,dis[a->y]+1);
			gap[dis[x]]--;
			if(!gap[dis[x]]) break;
			gap[dis[x] = mindis]++;
			if(x != s) x = pre[x];
		} else {
			pre[ar->y] = x;
			x = ar->y;
		}
	}
	return maxflow;
}
