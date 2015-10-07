<TeX>返回凸包上最远点对距离</TeX>
double RC(int N) {
	double ans = 0.0;
	Hull[N] = Hull[0];
	int to = 1;
	for(int i = 0;i < N;i++) {
		while((Hull[i+1]-Hull[i])*(Hull[to]-Hull[i]) < (Hull[i+1]-Hull[i])*(Hull[to+1]-Hull[i])) to = (to+1)%N;
		ans = max(ans,(Hull[i]-Hull[to]).lensqr());
		ans = max(ans,(Hull[i+1]-Hull[to]).lensqr());
	}
	return sqrt(ans);
}
