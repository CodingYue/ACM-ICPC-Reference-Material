<TeX>
	多边形面积并 $O(n^2logn)$
</TeX>
struct Polygon {
	int M;
	vector<Point> p;
	void init() {
		p.resize(M);
		for (int i = 0; i < M; ++i) p[i].init();
		if (dcmp((p[1]-p[0]) * (p[2]-p[1])) < 0) reverse(p.begin(), p.end());
		p.push_back(p[0]);
	}
	Point& operator [](const int &i) { return p[i]; }
} poly[MaxN];
double xmul(Point a, Point b, Point c) { return (b-a)*(c-a); }
pair<double, int> keys[MaxN];
double get(Point a, Point b, Point c) {
	double t;
	if (fabs(a.x-b.x) > eps) t = (c.x-a.x)/(b.x-a.x);
	else t = (c.y-a.y)/(b.y-a.y);
	t = max(min(t,1.0),0.0);
	return t;
}
double solve(int n) {
	double res = 0;
	for (int i = 0; i < n; ++i)
	for (int x = 0; x < poly[i].M; ++x) {
		int keysize = 0;
		for (int k = 0; k < n; ++k) if (k != i)
		for (int y = 0; y < poly[k].M; ++y) {
			int t1 = dcmp(xmul(poly[i][x], poly[i][x+1], poly[k][y]));
			int t2 = dcmp(xmul(poly[i][x], poly[i][x+1], poly[k][y+1]));
			if (!t1 && !t2) {
				if (k < i && dcmp((poly[k][y+1]-poly[k][y])%(poly[i][x+1]-poly[i][x])) >= 0) {
					double d1 = get(poly[i][x], poly[i][x+1], poly[k][y]);
					double d2 = get(poly[i][x], poly[i][x+1], poly[k][y+1]);
					keys[keysize++] = make_pair(d1, 1);
					keys[keysize++] = make_pair(d2, -1);
				}
			} else if ((t1 >= 0 && t2 < 0) || (t1 < 0 && t2 >= 0)) {
				double d1 = xmul(poly[k][y], poly[k][y+1], poly[i][x]);
				double d2 = xmul(poly[k][y], poly[k][y+1], poly[i][x+1]);
				int t = 1; if (t2 >= 0) t = -1;
				keys[keysize++] = make_pair(max(min(d1/(d1-d2),1.),0.), t);
			}
		}
		sort(keys, keys + keysize);
		int cnt = 0;
		double s = 0, tmp = 0;
		bool f = 1;
		for (int j = 0; j < keysize; ++j) {
			cnt += keys[j].second;
			if (!cnt && !f) tmp = keys[j].first, f = 1;
			if (cnt && f) s += keys[j].first - tmp, f = 0;
		}
		s += 1. - tmp;
		res += (poly[i][x] * poly[i][x+1]) * s;
	}
	return res * 0.5;
}
