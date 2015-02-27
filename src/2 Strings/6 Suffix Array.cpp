int aa[222222], ab[222222];
int *rank,*last_rank,*ysorted;
int sa[222222];
char Str[222222];

int cmp(int l,int r,int step) {
	return last_rank[l] == last_rank[r] && last_rank[l+step] == last_rank[r+step];
}

int rw[222222];
void rsort(int n,int m) {
	for(int i = 0;i < m;i++) rw[i] = 0;
	for(int i = 0;i < n;i++) rw[rank[ysorted[i]]]++;
	for(int i = 1;i < m;i++) rw[i] += rw[i-1];
	for(int i = n-1;i >= 0;i--) sa[--rw[rank[ysorted[i]]]] = ysorted[i]; // keep order
}

void da(int n,int m) { // n = strlen, m = alphabet size
	rank = aa; last_rank = ab; ysorted = ab;
	for(int i = 0;i < n;i++) { rank[i] = Str[i]; ysorted[i] = i; }
	rsort(n,m);
	
	int p = 0; // different suffix cnt.
	for(int step = 1;p < n;step *= 2, m = p) {
		ysorted = last_rank; // recycle use
		
		int cnt = 0;
		for(int i = n-step;i < n;i++) ysorted[cnt++] = i;
		for(int i = 0;i < n;i++) if(sa[i] >= step) ysorted[cnt++] = sa[i]-step;
		rsort(n,m);
		
		last_rank = rank;
		rank = ysorted;
		p = 1;
		rank[sa[0]] = 0;
		for(int i = 1;i < n;i++) rank[sa[i]] = cmp(sa[i],sa[i-1],step)?p-1:p++;
	}
}

int height[222222]; // lcp of <TeX>suffix$_i$ and suffix$_{i-1}$</TeX>
void get_height(int n) {
	int k = 0;
	for(int i = 0;i < n;i++) {
		if(rank[i] == 0) k = height[rank[i]] = 0;
		else {
			if(k > 0) k--;
			int j = sa[rank[i]-1];
			while(Str[i+k]==Str[j+k]) k++;
			height[rank[i]] = k;
		}
	}
}

int lcp(int i,int j) {
	if(i == j) return n-i;
	if(rank[i] > rank[j]) swap(i,j);
	return rmq_querymin(rank[i]+1,rank[j]);
}
