<TeX> 半平面交.. 直线的左侧
 需注意半平面的方向！
 不等式有解等价与 $cnt > 1$ </TeX>
struct Segment {
	Point s, e;
	double angle;
	Segment(){}
	Segment(Point s, Point e)
		: s(s), e(e) {
			angle = atan2(e.y - s.y, e.x - s.x);
		}
} ;
Point get_intersect(Segment s1, Segment s2) {
	double u = xmul(s1.s, s1.e, s2.s);
	double v = xmul(s1.e, s1.s, s2.e);
	Point t;
	t.x = (s2.s.x * v + s2.e.x * u) / (u + v);
	t.y = (s2.s.y * v + s2.e.y * u) / (u + v);
	return t;
}
bool cmp(Segment a, Segment b) {
	if (dcmp(a.angle - b.angle) == 0) return dcmp(xmul(a.s, a.e, b.s)) < 0;
	return dcmp(a.angle - b.angle) < 0;
	return 0;
}
bool IsParallel(Segment P, Segment Q) {
	return dcmp((P.e - P.s) * (Q.e - Q.s)) == 0;
}
Segment deq[MaxN];
int HalfPlaneIntersect(Segment seg[], int n, Point hull[]) {
	sort(seg, seg + n, cmp);
	int tmp = 1;
	for (int i = 1; i < n; ++i) {
		if (dcmp(seg[i].angle - seg[tmp - 1].angle) != 0) {
			seg[tmp++] = seg[i];
		}
	}
	n = tmp;
	deq[0] = seg[0]; deq[1] = seg[1];
	int front = 0, tail = 1;
	for (int i = 2; i < n; ++i) {
		if(IsParallel(deq[tail], deq[tail-1]) || IsParallel(deq[front], deq[front+1])) return 0;
		while (front < tail && dcmp(xmul(seg[i].s, seg[i].e, get_intersect(deq[tail], deq[tail - 1]))) < 0) --tail;
		while (front < tail && dcmp(xmul(seg[i].s, seg[i].e, get_intersect(deq[front], deq[front+1]))) < 0) ++front;
		deq[++tail] = seg[i];
	}
	while(front < tail && xmul(deq[front].s, deq[front].e, get_intersect(deq[tail], deq[tail-1])) < -eps) tail--;
	while(front < tail && xmul(deq[tail].s, deq[tail].e, get_intersect(deq[front], deq[front+1])) < -eps) front++;
	int cnt = 0;
	deq[++tail] = deq[front];
	for (int i = front; i < tail; ++i) hull[cnt++] = get_intersect(deq[i], deq[i+1]);
	return cnt;
}