struct Point3D {
	double x, y, z;
	Point3D(){}
	Point3D(double x, double y, double z)
		: x(x), y(y), z(z) {}
	Point3D operator -(const Point3D &b) {
		return Point3D(x - b.x, y - b.y, z - b.z);
	}
	Point3D operator /(const double &t) {
		return Point3D(x / t, y / t, z / t);
	}
	Point3D operator +(const double &t) {
		return Point3D(x + t, y + t, z + t);
	}
	Point3D operator +(const Point3D &b) {
		return Point3D(x + b.x, y + b.y, z + b.z);
	}
	Point3D operator *(const double &t) {
		return Point3D(x * t, y * t, z * t);
	}
	double operator %(const Point3D &b) {
		return x * b.x + y * b.y + z * b.z;
	}
	Point3D operator *(const Point3D &b) {
		double i = y * b.z - b.y * z;
		double j = z * b.x - x * b.z;
		double k = x * b.y - b.x * y;
		return Point3D(i, j, k);
	}
	double len() {
		return sqrt( sqr(x) + sqr(y) + sqr(z) );
	}
	void init() {
		scanf("%lf%lf%lf",&x,&y,&z);
	}
};