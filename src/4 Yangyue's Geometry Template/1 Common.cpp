int dcmp(double a, double b) {
	if (fabs(a - b) < eps) return 0;
	if (b - a > eps) return -1;
	return 1;
}
int dcmp0(double x) {
	if (x > eps) return 1;
	if (x < -eps) return -1;
	return 0;
}

struct Point {
	double x, y;
	Point(){}
	Point(double x, double y) : x(x), y(y) {}
	double operator * (const Point &b) {
		return x * b.y - y * b.x;
	}
	Point operator - (const Point &b) {
		return Point(x - b.x, y - b.y);
	}
	Point operator + (const Point &b) {
		return Point(x + b.x, y + b.y);
	}
	Point operator / (const double &t) {
		return Point(x / t, y / t);
	}
	Point operator * (const double &t) {
		return Point(x * t, y * t);
	}
	double operator %(const Point &b) {
		return x * b.x + y * b.y;
	}
	bool operator < (const Point &b) const {
		if (dcmp(x, b.x) != 0) return dcmp(x, b.x) < 0;
		return dcmp(y, b.y) < 0;
	}
	bool operator == (const Point &b) const {
		if (dcmp(x, b.x) != 0) return 0;
		if (dcmp(y, b.y) != 0) return 0;
		return 1;
	}
};