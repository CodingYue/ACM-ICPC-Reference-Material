<TeX>k短无环路径。邻接矩阵G存图，然后调用yenLoopless即可，s是起点，t终点，n点数，k是k。</TeX>
const int MAXN = 50;
const int INF = 0x3F3F3F3F;

class PATH
{
public:
	int node[MAXN];
	int nodecnt;
	int block[MAXN];
	int blockcnt;
	int len;
	int dev;

	PATH(int v = 0) { memset(this,0,sizeof(PATH)); node[nodecnt++] = v; }
	bool operator>(const PATH& p) const
	{
		if(len != p.len)
			return len > p.len;
		else
		{
			for(int i = p.nodecnt-1,j = nodecnt-1;i >= 0 && j >= 0;i--,j--)
			{
				if(p.node[i] != node[j]) return node[j] > p.node[i];
			}
			return nodecnt > p.nodecnt;
		}
		return false;
	}
};

int dis[MAXN];
int pre[MAXN];
int G[MAXN][MAXN];
bool vis[MAXN];

bool block[MAXN][MAXN];

// O(n^2)
int dijkstra(int n)
{
	for (int p = 0;p < n;p++)
	{
		int minV = -1;
		for (int i = 0; i < n; i++)
		{
			if (!vis[i] && (minV == -1 || dis[i] < dis[minV])) minV = i;
		}
		if (minV == -1) break;
		vis[minV] = true;

		for(int to = 0;to < n;to++)
		{
			if(!vis[to] && !block[minV][to])
			{
				int len = G[minV][to];
				if(dis[to] > dis[minV]+len || (dis[to] == dis[minV]+len && minV < pre[to]))
				{
					dis[to] = dis[minV]+len;
					pre[to] = minV;
				}
			}
		}
	}
	return 0;
}

PATH shortestPath(int v)
{
	PATH p(v);
	p.len = dis[v];
	for (v = pre[v];v != -1;v = pre[v]) p.node[p.nodecnt++] = v;
	reverse(p.node,p.node+p.nodecnt);
	return p;
}

int delSubpath(const PATH& p, int dev)
{
	int last = p.node[0];
	vis[last] = true;
	int v;
	for (int i = 1; dev != i; i++)
	{
		v = p.node[i];
		pre[v] = last;
		dis[v] = dis[last]+G[last][v];
		vis[v] = true;
		last = v;
	}
	vis[last] = false;
	return 0;
}

int initSingleSrc(int s)
{
	memset(dis,0x3F,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	memset(vis,0,sizeof(vis));
	dis[s] = 0;
	return 0;
}

int yenLoopless(int s,int t,int n,int k)
{
	PATH result[201];
	int cnt = 0;

	priority_queue< PATH, vector<PATH>, greater<PATH> > candidate;
	memset(block,0,sizeof(block));
	initSingleSrc(s);
	dijkstra(n);
	if (dis[t] < INF)
	{
		PATH sh = shortestPath(t);
		sh.dev = 1;
		sh.block[sh.blockcnt++] = sh.node[sh.dev];
		candidate.push(sh);
	}
	while (cnt < k && !candidate.empty())
	{
		PATH p = candidate.top();
		candidate.pop();

		memset(block, 0, sizeof(block));
		int dev = p.dev;
		while (dev < p.nodecnt)
		{
			int last = p.node[dev-1];
			if (dev == p.dev)
			{
				for (int i = 0; i < p.blockcnt; i++)
				{
					block[last][p.block[i]] = true;
				}
			}
			else block[last][p.node[dev]] = true;

			initSingleSrc(s);
			delSubpath(p,dev);
			dijkstra(n);

			if (dis[t] < INF)
			{
				PATH newP = shortestPath(t);
				newP.dev = dev;
				if (dev == p.dev)
				{
					newP.blockcnt = p.blockcnt;
					memcpy(newP.block,p.block,sizeof(newP.block));
				}
				else newP.block[newP.blockcnt++] = p.node[dev];
				newP.block[newP.blockcnt++] = newP.node[dev];
				candidate.push(newP);
			}

			dev++;
		}
		result[cnt++] = p;
	}
	if (cnt < k) puts("No");
	else
	{
		int len = result[k-1].nodecnt;
		printf("%d",result[k-1].node[len-1]+1);
		for (int i = len-2; i >= 0; i--)
			printf("-%d",result[k-1].node[i]+1);
		putchar('\n');
	}
	return 0;
}