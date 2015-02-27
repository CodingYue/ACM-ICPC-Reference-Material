int MinDivi[MAXNUM], Prime[MAXNUM/10], Miu[MAXNUM], Phi[MAXNUM];
int PCnt = 0;

void era(int N) {
	for(int i = 2;i <= N;i++) {
		if(!MinDivi[i]) {
			Prime[PCnt++] = i; MinDivi[i] = i;
			Miu[i] = -1; Phi[i] = i-1;
		}
		for(int j = 0;j < PCnt && Prime[j] <= MinDivi[i] && i*Prime[j] <= N;j++) {
			MinDivi[i*Prime[j]] = Prime[j];
			Miu[i*Prime[j]] = -Miu[i];
			if(Prime[j] == MinDivi[i]) Miu[i*Prime[j]] = 0;
			Phi[i*Prime[j]] = Phi[i]*(Prime[j]-(Prime[j] != MinDivi[i]));
		}
	}
}
