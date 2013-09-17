//判规范相交
bool stdcross(Point A, Point B, Point C, Point D) {
	int t1, t2;
	t1 = dcmp0((C - A) * (B - A));
	t2 = dcmp0((D - A) * (B - A));
	if (t1 * t2 >= 0) return 0;
	t1 = dcmp0((B - C) * (D - C));
	t2 = dcmp0((A - C) * (D - C));
	if (t1 * t2 >= 0) return 0;
	return 1;
}

//点是否在线段上
bool PinSeg(Point P, Point A, Point B) {
	if (dcmp0((P - A) * (B - A)) != 0) return 0;
	if (dcmp(P.x, min(A.x, B.x)) < 0 || dcmp(P.x, max(A.x, B.x)) > 0) return 0;
	if (dcmp(P.y, min(A.y, B.y)) < 0 || dcmp(P.y, max(A.y, B.y)) > 0) return 0;
	return 1;
}

//非规范相交
bool unstdcross(Point A, Point B, Point C, Point D) {
	if (stdcross(A, B, C, D)) return 1;
	if (PinSeg(A, C, D)) return 1;
	if (PinSeg(B, C, D)) return 1;
	if (PinSeg(C, A, B)) return 1;
	if (PinSeg(D, A, B)) return 1;
}

//相交不重合线段求交点
Point getcrossPoint(Point A, Point B, Point C, Point D) {
	if (PinSeg(A, C, D)) return A;
	if (PinSeg(B, C, D)) return B;
	if (PinSeg(C, A, B)) return C;
	if (PinSeg(D, A, B)) return D;
	double S1 = fabs((C - A) * (B - A));
	double S2 = fabs((D - A) * (B - A));
	double k = S2 / (S1 + S2);
	Point vect = C - D;
	return Point(D.x + k * vect.x, D.y + k * vect.y);
}
