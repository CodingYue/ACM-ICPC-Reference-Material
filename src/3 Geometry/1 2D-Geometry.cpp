<TeX>
	eps 设置成$1e-8$
</TeX>
struct Point {
	double x, y;
	Point (){}
	Point(double x, double y) : x(x), y(y) {}
	Point operator - (const Point &b) { return Point(x - b.x, y - b.y); }
	Point operator + (const Point &b) { return Point(x + b.x, y + b.y); }
	Point operator * (const double &b) { return Point(x * b, y * b); }
	Point rot90() { return Point(-y, x); }
	Point rot(double ang) { return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang)); }
	double ang() { double res = atan2(y, x); if (dcmp(res) < 0) res += pi * 2; return res; }
	double operator * (const Point &b) { return x * b.y - y * b.x; }
	double operator % (const Point &b) { return x * b.x + y * b.y; }
	double len2() { return x * x + y * y; }
	double len() { return sqrt(x * x + y * y); }
};
struct Line {
	Point s, e;
	Line(){}
	Line(Point s, Point e) : s(s), e(e) {}
};
inline double xmul(Point a, Point b, Point c) {
	return (c - a) * (c - b);
}
//点p 到直线{p1, p2} 距离
double disLP(Point p1, Point p2, Point q) {
	return fabs((p1 - q) * (p2 - q)) / (p1 - p2).len();
}
// 平面几何
// 点q 到线段{p1, p2} 的距离
double dis_Seg_P(Point p1, Point p2, Point q) {
	if ((p2 - p1) % (q - p1) < eps) return (q - p1).len();
	if ((p1 - p2) % (q - p2) < eps) return (q - p2).len();
	return disLP(p1, p2, q);
}
// hit on the edge will return true
bool is_segment_intersect(Point A, Point B, Point C,Point D) {
	if(max(C.x,D.x) < min(A.x,B.x) || max(C.y,D.y) < min(A.y,B.y)) return false;
	if(max(A.x,B.x) < min(C.x,D.x) || max(A.y,B.y) < min(C.y,D.y)) return false;
	if(dcmp((B-A)*(C-A))*dcmp((B-A)*(D-A)) > 0) return false;
	if(dcmp((D-C)*(A-C))*dcmp((D-C)*(B-C)) > 0) return false;
	return true;
}
//两直线交点
Point get_intersect(Line s1, Line s2) { 
	double u = xmul(s1.s, s1.e, s2.s);
	double v = xmul(s1.e, s1.s, s2.e);
	Point t;
	t.x = (s2.s.x * v + s2.e.x * u) / (u + v);
	t.y = (s2.s.y * v + s2.e.y * u) / (u + v);
	return t;
}
// 点P 是否在直线{p1, p2} 上
bool is_point_onseg(Point p1,Point p2,Point P)
{
	if(! (min(p1.x,p2.x) <= P.x && P.x <= max(p1.x,p2.x) &&
		  min(p1.y,p2.y) <= P.y && P.y <= max(p1.y,p2.y)) )
		return false;
	if(dcmp((P-p1)*(p2-p1)) == 0) return true;
	return false;
}
// 点q 到直线{p1, p2} 垂足
Point proj(Point p1, Point p2, Point q) {
	return p1 + ((p2 - p1) * ((p2 - p1) % (q - p1) / (p2 - p1).len()));
}
// 直线与圆的交点
vector<Point> getCL(Point c, double r, Point p1, Point p2) { 
	vector<Point> res;
	double x = (p1 - c) % (p2 - p1);
	double y = (p2 - p1).len2();
	double d = x * x - y * ((p1 - c).len2() - r * r);
	if (d < -eps) return res;
	if (d < 0) d = 0;
	Point q1 = p1 - ((p2 - p1) * (x / y));
	Point q2 = (p2 - p1) * (sqrt(d) / y);
	res.push_back(q1 + q2);
	res.push_back(q1 - q2);
	return res;
}
// 圆与圆的交点
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
// 两圆公共面积.
double areaCC(Point c1, double r1, Point c2, double r2) {
	double d = (c1 - c2).len();
	if (r1 + r2 < d + eps) return 0;
	if (d < fabs(r1 - r2) + eps) {
		double r = min(r1, r2);
		return r * r * pi;
	}
	double x = (d * d + r1 * r1 - r2 * r2) / (2 * d);
	double t1 = acos(x / r1);
	double t2 = acos((d - x) / r2);
	return r1 * r1 * t1 + r2 * r2 * t2 - d * r1 * sin(t1);
}
// ccenter 返回{p1, p2, p3} 的外接圆圆心, formula
// 四点在同一圆周
bool onCir(Point p1, Point p2, Point p3, Point p4) {
	if (fabs((p2 - p1) * (p3 - p1)) < eps) return true;
	Point c = ccenter(p1, p2, p3);
	return fabs((c - p1).len2() - (c - p4).len2()) < eps;
}
//两圆公切线, 先返回内公切线, 后面是外公切线
vector<Line> getLineCC(Point c1, double r1, Point c2, double r2) {
	vector<Line> res;
	double d = (c1 - c2).len();
	if (fabs(d - r1 - r2) < eps) {
		Point o = (c1 + c2) * 0.5;
		res.push_back(Line(o, o + (c1 - c2).rot90()));
		res.push_back(res[res.size() - 1]);
	} else {
		double ang = acos((r1 + r2) / d);
		res.push_back(Line(c1 + ((c2 - c1) * (r1 / d)).rot(ang), c2 + ((c1 - c2) * (r2 / d)).rot(ang)));
		ang = -ang;
		res.push_back(Line(c1 + ((c2 - c1) * (r1 / d)).rot(ang), c2 + ((c1 - c2) * (r2 / d)).rot(ang)));
	}
	double ang = acos((r2 - r1) / d);
	res.push_back(Line(c1 + ((c1 - c2) * (r1 / d)).rot(ang), c2 + ((c1 - c2).rot(ang) * (r2 / d))));
	ang = -ang;
	res.push_back(Line(c1 + ((c1 - c2) * (r1 / d)).rot(ang), c2 + ((c1 - c2).rot(ang) * (r2 / d))));
	return res;
}
