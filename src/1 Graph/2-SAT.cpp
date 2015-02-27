<TeX>顺便提一句2SAT输出方案如果要字典序最小的话有个非常蠢的暴力做法，顺序考虑每个点的两种状态，然后类似bfs一样暴力去确定其前趋后继。
正常的么下面这样做就行了，$rev_i$ 是 $i$ 相对的点，$choose_i$ 为$i$点是否要选在方案中，保证一对点恰有一个在方案中。</TeX>

bool twoSAT(int n) {
	for(int i = 0;i < 2*n;i++) if(!DFN[i]) tarjan(i);
	for(int i = 0;i < 2*n;i++) {
		if(SCC[i] == SCC[rev[i]]) return false;
		choose[i] = SCC[i] < SCC[rev[i]];
	}
	return true;
}
