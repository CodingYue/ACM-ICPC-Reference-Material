const double eps = 1e-8;

inline double dcmp(double x) { return x < -eps ? -1 : x > eps; }
inline double xmul(Point a, Point b, Point c) {
	return (c - a) * (c - b);
}
// hit on the edge will return true
bool is_segment_intersect(const Point& A,const Point& B,const Point& C,const Point& D) {
	if(max(C.x,D.x) < min(A.x,B.x) || max(C.y,D.y) < min(A.y,B.y)) return false;
	if(max(A.x,B.x) < min(C.x,D.x) || max(A.y,B.y) < min(C.y,D.y)) return false;
	if(dcmp((B-A)*(C-A))*dcmp((B-A)*(D-A)) > 0) return false;
	if(dcmp((D-C)*(A-C))*dcmp((D-C)*(B-C)) > 0) return false;
	return true;
}
Point get_intersect(Segment s1, Segment s2) {
	double u = xmul(s1.s, s1.e, s2.s);
	double v = xmul(s1.e, s1.s, s2.e);
	Point t;
	t.x = (s2.s.x * v + s2.e.x * u) / (u + v);
	t.y = (s2.s.y * v + s2.e.y * u) / (u + v);
	return t;
}
bool is_point_onseg(const Point& LineA,const Point& LineB,const Point& P)
{
	if(! (min(LineA.x,LineB.x) <= P.x && P.x <= max(LineA.x,LineB.x) &&
		  min(LineA.y,LineB.y) <= P.y && P.y <= max(LineA.y,LineB.y)) )
		return false;
	if(dcmp((P-LineA)*(LineB-LineA)) == 0) return true;
	return false;
}

