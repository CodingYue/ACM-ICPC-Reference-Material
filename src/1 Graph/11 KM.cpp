
int n,nx,ny, m;
int link[MaxN],lx[MaxN],ly[MaxN],slack[MaxN]; 
int visx[MaxN],visy[MaxN],w[MaxN][MaxN];

int DFS(int x)
{
	visx[x] = 1;
	for (int y = 1;y <= ny;y ++)
	{
		if (visy[y])
			continue;
		int t = lx[x] + ly[y] - w[x][y];
		if (t == 0)       //
		{
			visy[y] = 1;
			if (link[y] == -1||DFS(link[y]))
			{
				link[y] = x;
				return 1;
			}
		}
		else if (slack[y] > t) 
			slack[y] = t;
	}
	return 0;
}
void KM()
{
	int i,j;
	memset (link,-1,sizeof(link));
	memset (ly,0,sizeof(ly));
	for (i = 1;i <= nx;i ++)       
		for (j = 1,lx[i] = -INF;j <= ny;j ++)
			if (w[i][j] > lx[i])
				lx[i] = w[i][j];

	for (int x = 1;x <= nx;x ++)
	{
		for (i = 1;i <= ny;i ++)
			slack[i] = INF;
		while (1)
		{
			memset (visx,0,sizeof(visx));
			memset (visy,0,sizeof(visy));
			if (DFS(x))    
				break;  
			int d = INF;
			for (i = 1;i <= ny;i ++)
				if (!visy[i]&&d > slack[i])
					d = slack[i];
			for (i = 1;i <= nx;i ++)
				if (visx[i])
					lx[i] -= d;
			for (i = 1;i <= ny;i ++) 
				if (visy[i])
					ly[i] += d;
				else
					slack[i] -= d;
		}
	}
}

