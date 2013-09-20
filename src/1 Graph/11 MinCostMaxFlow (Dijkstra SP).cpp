<TeX>
% 测试题目 BZOJ 1061, 1834, 1877
如果点数真的很少，可以把Dijkstra改成$O(n^2)$的实现，然后换成邻接矩阵，可以快不少。
</TeX>

bool vis[MAXN];
int d1[MAXN],dis[MAXN],pre[MAXN],Queue[MAXN];;
ARC* prearc[MAXN];
int dijkstra(int s,int t,int n)
{
	memset(vis,0,sizeof(vis[0])*n);
	memset(dis,0x7F,sizeof(*dis)*n);
	set<pii> q; dis[s] = 0;
	q.insert(pii(dis[s]-d1[s],s));
	while(!q.empty())
	{
		set<pii>::iterator it = q.begin();
		int x = it->second;
		int xdis = dis[x];
		q.erase(it);
		vis[x] = true;
		for(ARC* a = Arc[x];a;a = a->Next)
		{
			if(a->c <= 0 || vis[a->y]) continue;
			if(xdis + a->w < dis[a->y])
			{
				q.erase(pii(dis[a->y]-d1[a->y],a->y));
				dis[a->y] = xdis + a->w;
				q.insert(pii(dis[a->y]-d1[a->y],a->y));
			}
		}
	}
	return dis[t];
}

bool bfs(int s,int t,int n)
{
	memset(vis,0,sizeof(vis[0])*n);
	int qf = 0;
	int qe = 0;
	vis[s] = true; Queue[qe++] = s;
	while(qf < qe)
	{
		int x = Queue[qf++];
		if(x == t) break;

		for(ARC* a = Arc[x];a;a = a->Next)
		{
			if(a->c <= 0) continue;
			if(!vis[a->y] && dis[x] + a->w == dis[a->y])
			{
				vis[a->y] = true;
				pre[a->y] = x;
				prearc[a->y] = a;
				Queue[qe++] = a->y;
			}
		}
	}
	return vis[t];
}

pii mincost_maxflow(int s,int t,int n)
{
	memset(d1,0,sizeof(d1[0])*n);
	int maxflow = 0;
	int mincost = 0;
	while(dijkstra(s,t,n) < INF)
	{
		while(bfs(s,t,n))
		{
			int tflow = INF;
			int tcost = dis[t];
			for(int x = t;x != s;x = pre[x]) tflow = min(tflow,prearc[x]->c);
			for(int x = t;x != s;x = pre[x])
			{
				prearc[x]->c -= tflow;
				prearc[x]->R->c += tflow;
			}
			mincost += tcost * tflow;
			maxflow += tflow;
		}
		memcpy(d1,dis,sizeof(d1[0])*n);
	}
	return pii(mincost,maxflow);
}