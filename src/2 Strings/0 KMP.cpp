<TeX> 求出 next 并返回 str 的循环周期。 用于匹配过程一样。</TeX>
int k_next[MAXLEN];
int kmp(char* str,int len) {
	int now = 0;
	for(int i = 1;i < len;i++) {
		while(now && str[i] != str[now]) now = k_next[now-1];
		if(str[i] == str[now]) now++;
		k_next[i] = now;
	}
	int period = len-(k_next[len-1]);
	if(len % period == 0) return period;
	return len;
}
