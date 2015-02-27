<TeX>
一些结论：

弦：连接环中不相邻的两个点的边。

弦图：一个无向图称为弦图当且仅当图中任意长度大于3的环都至少有一个弦。

单纯点：设N(v)表示与点v相邻的点集。一个点称为单纯点当{v} + N(v)的诱导子图为一个团。

完美消除序列：这是一个序列{v[i]}，它满足v[i]在{v[i..n]}的诱导子图中为单纯点。

弦图的判定：存在完美消除序列的图为弦图。可以用MCS最大势算法求出完美消除序列。

最大势算法 从n到1的顺序依次给点标号(标号为i的点出现在完美消除序列的第i个)。
设label[i]表示第i个点与多少个已标号的点相邻，每次选择label[i]最大的未标号的点进行标号。

判断一个序列是否为完美消除序列： 设{vi+1,…,vn}中所有与vi相邻的点依次为vj1,…, vjk。只需判断vj1是否与vj2,…, vjk相邻即可。
弦图的最大点独立集——完美消除序列从前往后能选就选。最小团覆盖数=最大点独立集数。</TeX>
int Label[10010], Order[10010], Seq[10010], Color[10010], Useable[10010];

int main(void) {
	int N, M;
	scanf("%d %d",&N,&M);
	for(int i = 0;i < M;i++) {
		int x,y;
		scanf("%d %d",&x,&y);
		insert_edge(x,y);
		insert_edge(y,x);
	}

	Label[0] = -5555;
	for(int i = N;i > 0;i--) {
		int t = 0;
		for(int j = 1;j <= N;j++) if(!Order[j] && Label[j] > Label[t]) t = j;
		Order[t] = i;
		Seq[i] = t;
		for(EDGE* e = E[t];e != NULL;e = e->Next) Label[e->y]++;
	}

	int ans = 0;
	for(int i = N;i > 0;i--) {
		for(EDGE* e = E[Seq[i]];e != NULL;e = e->Next)
			Useable[Color[e->y]] = i;
		int c = 1;
		while(Useable[c] == i) c++;
		Color[Seq[i]] = c;
		if(c > ans) ans = c;
	}
	printf("%d\n",ans);
	return 0;
}
