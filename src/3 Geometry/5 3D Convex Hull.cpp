struct Hull3D {
	struct Plane {
		int a, b, c;
		bool ok;
		Plane(){}
		Plane(int a, int b, int c, bool ok)
			: a(a), b(b), c(c), ok(ok) {}
	};
	int n, tricnt;        //初始点数
	int vis[MaxN][MaxN];  //点i到点j是属于哪个面
	Plane tri[MaxN << 2]; //凸包三角形
	Point3D Ply[MaxN];    //初始点
	double dist(Point3D a) {
		return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); 
	}
	double area(Point3D a, Point3D b, Point3D c) {
		return dist((b - a) * (c - a));
	}
	double volume(Point3D a, Point3D b, Point3D c, Point3D d) {
		return ((b - a) * (c - a)) % (d - a);
	}
	double PtoPlane(Point3D &P, Plane f) {  // 正 : 面同向{
		Point3D m = Ply[f.b] - Ply[f.a];
		Point3D n = Ply[f.c] - Ply[f.a];
		Point3D t = P - Ply[f.a];
		return (m * n) % t;
	}
	void deal(int p, int a, int b) {
		int f = vis[a][b];
		Plane add;
		if (tri[f].ok) {
			if ((PtoPlane(Ply[p], tri[f])) > eps) dfs(p, f);
			else {
				add = Plane(b, a, p, 1);
				vis[p][b] = vis[a][p] = vis[b][a] = tricnt;
				tri[tricnt++] = add;
			}
		}
	}
	void dfs(int p, int cnt) { // 维护凸包，如果点p在凸包外更新凸包
		tri[cnt].ok = 0;
		deal(p, tri[cnt].b, tri[cnt].a);
		deal(p, tri[cnt].c, tri[cnt].b);
		deal(p, tri[cnt].a, tri[cnt].c);
	}
	bool same(int s, int e) { //判面是否相同
		Point3D a = Ply[tri[s].a];
		Point3D b = Ply[tri[s].b];
		Point3D c = Ply[tri[s].c];
		return fabs(volume(a, b, c, Ply[tri[e].a])) < eps
			&& fabs(volume(a, b, c, Ply[tri[e].b])) < eps
			&& fabs(volume(a, b, c, Ply[tri[e].c])) < eps;
	}
	void construct() { //构造凸包
		tricnt = 0;
		if (n < 4) return;
		bool tmp = 1;
		for (int i = 1; i < n; ++i) { // 两两不共点
			if (dist(Ply[0] - Ply[i]) > eps) {
				swap(Ply[1], Ply[i]);
				tmp = 0;
				break;
			}
		}
		if (tmp) return;
		tmp = 1;
		for (int i = 2; i < n; ++i) { //前三点不共线
			if ((dist((Ply[0] - Ply[1]) * (Ply[1] - Ply[i]))) > eps) {
				swap(Ply[2], Ply[i]);
				tmp = 0;
				break;
			}
		}
		if (tmp) return;
		tmp = 1;
		for (int i = 3; i < n; ++i) { //前四点不共面
			if (fabs((Ply[0] - Ply[1]) * (Ply[1] - Ply[2]) % (Ply[0] - Ply[i])) > eps) {
				swap(Ply[3], Ply[i]);
				tmp = 0;
				break;
			}
		}
		if (tmp) return;
		Plane add;
		for (int i = 0; i < 4; ++i) { //初始四面体
			add = Plane((i + 1) % 4, (i + 2) % 4, (i + 3) % 4, 1);
			if (PtoPlane(Ply[i], add) > 0) swap(add.b, add.c);
			vis[add.a][add.b] = vis[add.b][add.c] = vis[add.c][add.a] = tricnt;
			tri[tricnt++] = add;
		}
		for (int i = 4; i < n; ++i) { //构建凸包
			for (int j = 0; j < tricnt; ++j) {
				if (tri[j].ok && (PtoPlane(Ply[i], tri[j])) > eps) {
					dfs(i, j);
					break;
				}
			}
		}
		int cnt = tricnt; tricnt = 0;
		for (int i = 0; i < cnt; ++i) { //删除无用的面
			if (tri[i].ok) {
				tri[tricnt++] = tri[i];
			}
		}
	}
	int Planepolygon() { //多少个面
		int res = 0;
		for (int i = 0; i < tricnt; ++i) {
			bool yes = 1;
			for (int j = 0; j < i; ++j) {
				if (same(i, j)) {
					yes = 0;
					break;
				}
			}
			if (yes) ++res;
		}
		return res;
	}
	// Volume = sigma(volume(p, a, b, c));  i = 0..tricnt - 1;
} Hull;
