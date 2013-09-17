<TeX> 非递归版本， NodeID 为全局ID。</TeX>
int BlockRoot[111111];
int NodeID[111111];
int TreeSize[111111];
int Depth[111111];
int HeavyChild[111111]; // 0 if not set
int fa[111111];
int Queue[111111];
int idx = 0;
int Decomposition(int s)
{
	int qfront = 0;
	int qend = 0;
	Queue[qend++] = s;
	while(qfront < qend)
	{
		int x = Queue[qfront++];
		TreeSize[x] = 1;
		for(EDGE* e = E[x];e;e = e->Next)
		{
			int y = e->y;
			if(y == fa[x]) continue;
			
			fa[y] = x;
			Depth[y] = Depth[x]+1;
			Queue[qend++] = y;
		}
	}
	for(int i = qend-1;i >= 0;i--)
	{
		int x = Queue[i];
		for(EDGE* e = E[x];e;e = e->Next)
		{
			int y = e->y;
			if(y == fa[x]) continue;
			TreeSize[x] += TreeSize[y];
			if(TreeSize[HeavyChild[x]] < TreeSize[y]) HeavyChild[x] = y;
		}
	}

	for(int i = qend-1;i >= 0;i--)
	{
		int x = Queue[i];
		if(x == HeavyChild[fa[x]]) continue;
		int t = x;
		while(t)
		{
			BlockRoot[t] = x;
			NodeID[t] = ++idx;
			t = HeavyChild[t];
		}
	}
	return 0;
}

int ColorNode(int x,int y,int nc)
{
    while(1)
    {
        if(Depth[BlockRoot[x]] > Depth[BlockRoot[y]]) swap(x,y);
         
        if(BlockRoot[x] == BlockRoot[y])
        {
            if(Depth[x] > Depth[y]) swap(x,y);
            Seg_Modify(NodeID[x],NodeID[y],nc,1,idx);
            break;
        }
        Seg_Modify(NodeID[BlockRoot[y]],NodeID[y],nc,1,idx);
        y = fa[BlockRoot[y]];
    }
    return 0;
}
