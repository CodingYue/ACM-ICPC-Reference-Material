// 空间几何
struct Point {
	double x, y, z;
	Point(){}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	Point operator + (const Point &b) { return Point(x + b.x, y + b.y, z + b.z); }
	Point operator - (const Point &b) { return Point(x - b.x, y - b.y, z - b.y); }
	Point operator * (const Point &b) { return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x); }
	Point operator * (const double &b) { return Point(x * b, y * b, z * b); }
	double operator % (const Point &b) { return x * b.x + y * b.y + z * b.z; }
	double len2() { return x * x + y * y + z * z; }
	double len() { return sqrt(x * x + y * y + z * z); }

};
// 返回直线{p1, p2} 上到{q1, q2} 的最近点
// 平行时 d = 0 
Point getLL(Point p1, Point p2, Point q1, Point q2) {
	Point p = q1 - p1;
	Point u = p2 - p1;
	Point v = q2 - q1;
	//len2 means len^2
	double d = u.len2() * v.len2() - (u % v) * (u % v);
	//if (abs(d) < eps) return NULL;
	double s = ((p % u) * v.len2() - (p % v) * (u % v)) / d;
	return p1 + u * s;
}
// 面与线的交点, d = 0 时线在面上或与面平行
// p 为面上某点, o 是平面法向量. {q1, q2} 是直线.
Point getPL(Point p, Point o, Point q1, Point q2) {
	double a = o % (q2 - p);
	double b = o % (q1 - p);
	double d = a - b;
	//if (abs(d) < eps) return NULL;
	return ((q1 * a) - (q2 * b)) * (1. / d);
}
// 平面与平面的交线
vector<Point> getFF(Point p1, Point o1, Point p2, Point o2) {
	vector<Point> res;
	Point e = o1 * o2;
	Point v = o1 * e;
	double d = o2 % v;
	if (fabs(d) < eps) return res;
	Point q = p1 + v * ((o2 % (p1 - p1)) / d);
	res.push_back(q);
	res.push_back(q + e);
	return res;
}
// 射线p1, p2 与球(c,r) 的p 与p1 的距离. 不相交返回-1.
double get(Point c, double r, Point p1, Point p2) {
	if ((p2 - p1) % (c - p1) < -eps) return -1.;
	Point v = (p2 - p1); v = v * (1 / v.len());
	double x = (c - p1) % v;
	v = p1 + v * x;
	double d = (v - c).len2();
	if (dcmp(d - r * r) >= 0) return -1.;
	d = (p1 - v).len() - sqrt(r * r - d);
	return d;
}