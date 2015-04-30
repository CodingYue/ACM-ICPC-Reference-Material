int G[30];
int ans = 0;
 
void dfs(int P, int X) {
	if (P == 0 && X == 0) {ans++; return;}
 
	int p = __builtin_ctz(P | X);
	int Q = P & ~G[p];
 
	while (Q) {
		int i = __builtin_ctz(Q);
		dfs(P & G[i], X & G[i]);
		Q &= ~(1<<i); P &= ~(1<<i); X |= (1<<i);
	}
}
 
int Bron_Kerbosch() {
	// remove loop
	for (int i=0; i<N; ++i) G[i] &= ~(1<<i);

	ans = 0;
	dfs((1<<N)-1, 0);
	return ans;
}
