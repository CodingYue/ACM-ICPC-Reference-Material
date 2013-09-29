double cal(Point c, double r, double ang1, double ang2) {
	double ang = ang2 - ang1;
	if (dcmp(ang) == 0) return 0;
	Point p1 = c + Point(r, 0).rot(ang1);
	Point p2 = c + Point(r, 0).rot(ang2);
	return r * r * (ang - sin(ang)) + p1 * p2;
}
bool rm[MaxN];
pair<double, int> keys[MaxN * 10];
vector<Point> getCC(Point c1, double r1, Point c2, double r2) { 
	vector<Point> res;
	double x = (c1 - c2).len2();
	double y = ((r1 * r1 - r2 * r2) / x + 1) / 2;
	double d = r1 * r1 / x - y * y;
	if (d < -eps) return res;
	if (d < 0) d = 0;
	Point q1 = c1 + (c2 - c1) * y;
	Point q2 = ((c2 - c1) * sqrt(d)).rot90();
	res.push_back(q1 - q2);
	res.push_back(q1 + q2);
	return res;
}
double solve(int cur, int n) {
	if (rm[cur]) return 0;
	int m = 0;
	for (int i = 0; i < n; ++i) if (i != cur && !rm[i]) {
		vector<Point> root = getCC(cir[cur].c, cir[cur].r, cir[i].c, cir[i].r);
		if (root.size() == 0) continue;
		double ang1 = (root[0] - cir[cur].c).ang();
		double ang2 = (root[1] - cir[cur].c).ang();
		if (dcmp(ang1 - ang2) == 0) continue;
		if (dcmp(ang1 - ang2) >= 0) {
			keys[m++] = make_pair(0, 1);
			keys[m++] = make_pair(ang2, -1);
			keys[m++] = make_pair(ang1, 1);
			keys[m++] = make_pair(2*pi, -1);
		} else {
			keys[m++] = make_pair(ang1, 1);
			keys[m++] = make_pair(ang2, -1);
		}
	}
	keys[m++] = make_pair(0, 0);
	keys[m++] = make_pair(2 * pi, - MaxN * 10);
	sort(keys, keys + m);
	double res = cal(cir[cur].c, cir[cur].r, 0, keys[0].first);
	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		cnt += keys[i].second;
		if (cnt == 0) res += cal(cir[cur].c, cir[cur].r, keys[i].first, keys[i+1].first);
		// area[cover[cur] + cnt] -= tarea;
		// area[cover[cnr] + cnt + 1] += tarea;
	}
	return res;
}
