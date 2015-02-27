/* Usage:
   for(int i = 0;i < N;i++) yOrder[i] = i;
   sort(P,P+N,cmp_x);
   double result = closest_pair(0,N); // Won't change array "P" */

POINT P[111111];
int yOrder[111111];
inline bool cmp_x(const POINT& a,const POINT& b) { return a.x==b.x?a.y<b.y:a.x<b.x; }
inline bool cmp_y(const int a,const int b) { return P[a].y==P[b].y?P[a].x<P[b].x:P[a].y<P[b].y; }

int thisY[111111];
// [l,r)
double closest_pair(int l,int r) {
	double ans = 1e100;
	if(r-l <= 6) {
		for(int i = l;i < r;i++)
			for(int j = i+1;j < r;j++)
				ans = min(ans,(P[i]-P[j]).hypot());
		sort(yOrder+l,yOrder+r,cmp_y);
		return ans;
	}

	int mid = (l+r)/2;
	ans = min(closest_pair(l,mid),closest_pair(mid,r));
	inplace_merge(yOrder+l,yOrder+mid,yOrder+r,cmp_y);
	
	int top = 0;
	double ll = P[mid].x;
	for(int i = l;i < r;i++) {
		double xx = P[yOrder[i]].x;
		if(ll-ans <= xx && xx <= ll+ans) thisY[top++] = yOrder[i];
	}

	for(int i = 0;i < top;i++)
		for(int j = i+1;j < i+4 && j < top;j++)
			ans = min(ans,(P[thisY[j]]-P[thisY[i]]).hypot());
	return ans;
}
