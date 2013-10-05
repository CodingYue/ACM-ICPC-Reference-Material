<TeX>
	圆的面积并. $area_i$表示恰好被覆盖i次的面积。普通面积并需要去除掉被包含或被内切的圆。getCC() 模板里有。eps 设成$1e-8$ 需要对圆去重.
</TeX>
double cal(Point c, double r, double ang1, double ang2) {
	double ang = ang2 - ang1;
	if (dcmp(ang) == 0) return 0;
	Point p1 = c + Point(r, 0).rot(ang1);
	Point p2 = c + Point(r, 0).rot(ang2);
	return r * r * (ang - sin(ang)) + p1 * p2;
}
bool rm[MaxN];
pair<double, int> keys[MaxN * 10];
vector<Point> getCC(){}
bool cmp(const pair<double,int> &a, const pair<double,int> &b) {
	if (dcmp(a.fi - b.fi) != 0) return dcmp(a.fi - b.fi) < 0;
	return a.se > b.se;
}
double solve(int cur, int n) {
	if (rm[cur]) return 0;
	int m = 0;
	for (int i = 0; i < n; ++i) if (i != cur && !rm[i]) {
		// if (cir[cur] 被 cir[i] 包含或内切) { ++cover[cur]; continue; }
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
	keys[m++] = make_pair(2 * pi, - 100000);
	sort(keys, keys + m, cmp);
	double res = cal(cir[cur].c, cir[cur].r, 0, keys[0].first);
	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		cnt += keys[i].second;
		if (cnt == 0) res += cal(cir[cur].c, cir[cur].r, keys[i].first, keys[i+1].first);
		// area[cover[cur] + cnt] -= tarea;
		// area[cover[cur] + cnt + 1] += tarea;
	}
	return res;
}