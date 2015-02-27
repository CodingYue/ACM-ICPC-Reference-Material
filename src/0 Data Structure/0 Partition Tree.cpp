int val[19][100100], lsize[19][100100], sorted[100100]; // sorted: [1,N], sorted needed

void build_dt(int l,int r,int depth=0) { // build_dt(1,N)
	if(l == r) return 0;
	int mid = (l+r)/2;
	int x = sorted[mid];
	int samecnt = mid-l+1;
	for(int i = l;i <= mid;i++) if(sorted[i] < x) samecnt--;
	
	int pl = l;
	int pr = mid+1;
	for(int i = l;i <= r;i++) {
		lsize[depth][i] = lsize[depth][i-1];
		if(val[depth][i] < x || (val[depth][i] == x && samecnt)) {
			if(val[depth][i] == x) samecnt--;
			val[depth+1][pl++] = val[depth][i];
			lsize[depth][i]++;
		}
		else val[depth+1][pr++] = val[depth][i];
	}
	build_dt(l,mid,depth+1); build_dt(mid+1,r,depth+1);
}

// query_kth(1,N,l,r,k)
int query_kth(int L,int R,int l,int r,int k,int depth=0) {
	if(l == r) return val[depth][l];
	int mid = (L+R)/2;
	int lc = lsize[depth][l-1] - lsize[depth][L-1];
	int rc = lsize[depth][r] - lsize[depth][L-1];
	int lr = l-L-lc; int rr = r-L-rc+1;
	if(rc - lc >= k) return query_kth(L,mid,L+lc,L+rc-1,k,depth+1);
	return query_kth(mid+1,R,mid+1+lr,mid+rr,k-(rc-lc),depth+1);
}
