<TeX>
求的是男性最优的稳定婚姻解。稳定即没有汉子更喜欢的妹子和妹子更喜欢的汉子两情相悦的情况。男性最优即不存在所有汉子都得到了他更喜欢的妹子的解。

orderM[i][j] 为汉子i第j喜欢的妹子，
preferF[i][j] 为妹子i心中汉子j是第几位

不停的让汉子在自己的偏好列表里按顺序去找妹子，妹子取最优即可 $O(n^2)$
</TeX>
int stableMarriage(int n) {
	memset(pairM,-1,sizeof(pairM));
	memset(pairF,-1,sizeof(pairF));
	int pos[MAXN] = {0};
	for(int i = 0;i < n;i++) {
		while(pairM[i] == -1) { // can be implemented using queue
			int wife = orderM[i][pos[i]++];
			int ex = pairF[wife];
			if(ex == -1 || preferF[wife][i] < preferF[wife][ex]) {
				pairM[i] = wife; pairF[wife] = i;
				if(ex != -1) {
					pairM[ex] = -1;
					i = ex; // take GREAT care
				}
			}
		}
	}
	return 0;
}
