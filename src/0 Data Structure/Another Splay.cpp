struct node {
	int f,ch[2],v,nl,nr,ans,s;
	node() {}
	void Init(int _v,int _f) {
		v = _v; f = _f; ch[0] = ch[1] = 0; s = abs(_v);
		nl = nr = 0; if (v > 0) nr = v; else nl = -v;
		ans = 0;
	}
}pt[MaxNode];

struct Splay {
	int root;
	void update(int t) {
		pt[t].s = pt[pt[t].ch[0]].s + pt[pt[t].ch[1]].s + abs(pt[t].v);
		pt[t].nr = max(0,pt[pt[t].ch[0]].nr + pt[t].v - pt[pt[t].ch[1]].nl) + pt[pt[t].ch[1]].nr;
		pt[t].nl = max(0,pt[pt[t].ch[1]].nl - pt[t].v - pt[pt[t].ch[0]].nr) + pt[pt[t].ch[0]].nl;
		if (pt[t].v > 0) { // node of boy
			pt[t].ans = pt[pt[t].ch[0]].ans + pt[pt[t].ch[1]].ans + min(pt[pt[t].ch[0]].nr + pt[t].v,pt[pt[t].ch[1]].nl);
		} else { // otherwise
			pt[t].ans = pt[pt[t].ch[0]].ans + pt[pt[t].ch[1]].ans + min(pt[pt[t].ch[0]].nr,pt[pt[t].ch[1]].nl - pt[t].v);
		}
	}
	void zig(int x,bool w) {
		int y = pt[x].f; if (root == y) root = x;
		pt[y].ch[!w] = pt[x].ch[w]; if (pt[x].ch[w]) pt[pt[x].ch[w]].f = y;
		pt[x].f = pt[y].f; if (root != x) pt[pt[y].f].ch[y == pt[pt[y].f].ch[1]] = x;
		pt[x].ch[w] = y; pt[y].f = x; update(y);
	}
	void splay(int x) {
		while (x != root) {
			if (pt[x].f == root) zig(x,x == pt[pt[x].f].ch[0]);
			else {
				int y = pt[x].f, z = pt[y].f;
				if (y == pt[z].ch[0]) if (x == pt[y].ch[0]) { zig(y,1); zig(x,1); } else { zig(x,0); zig(x,1); }
				else if (x == pt[y].ch[0]) { zig(x,1); zig(x,0); } else { zig(y,0); zig(x,0); }
			}
		} update(x);
	}
	void splay(int x,int f) {
		while (pt[x].f != f) {
			if (pt[pt[x].f].f == f) zig(x,x == pt[pt[x].f].ch[0]);
			else {
				int y = pt[x].f, z = pt[y].f;
				if (y == pt[z].ch[0]) if (x == pt[y].ch[0]) { zig(y,1); zig(x,1); } else { zig(x,0); zig(x,1); }
				else if (x == pt[y].ch[0]) { zig(x,1); zig(x,0); } else { zig(y,0); zig(x,0); }
			}
		} update(x);
	}
	int selFlag;
	int sel(int Key) {
		int t = root;
		while (1) {
			int ls = pt[pt[t].ch[0]].s;
			if (ls < Key && ls + abs(pt[t].v) >= Key) {
				selFlag = Key - ls;
				return t;
			}
			if (Key <= ls) t = pt[t].ch[0]; else {
				Key -= ls + abs(pt[t].v);
				t = pt[t].ch[1];
			}
		} return t;
	}
	void Del(int t) {
		while (pt[t].ch[0] + pt[t].ch[1]) if (pt[t].ch[0]) zig(pt[t].ch[0],1); else zig(pt[t].ch[1],0); 
		if (root == t) {
			root = 0; return ;
		}
		pt[pt[t].f].ch[t == pt[pt[t].f].ch[1]] = 0; splay(pt[t].f);
	}
	int bound(int x,bool w) {
		splay(x);
		int ret = pt[x].ch[w];
		while (pt[ret].ch[!w]) ret = pt[ret].ch[!w];
		return ret;
	}
	PII Split(int t,int pos) {// break node t at postion pos
		int L = bound(t,0), R = bound(t,1); Del(t);
		splay(L,0); splay(R,L); 
		int s = abs(pt[t].v); int c = (pt[t].v > 0) ? 1 : -1;
		if (pos >= 1) {
			pt[++now].Init(c * (pos),R); pt[R].ch[0] = now;
			splay(now); L = now; splay(R,L);
		}
		if (pos < abs(pt[t].v)) {
			pt[++now].Init(c * (abs(pt[t].v) - pos),R); pt[R].ch[0] = now;
			splay(now); R = now; 
		}
		return MP(L,R);
	}
}Tab;