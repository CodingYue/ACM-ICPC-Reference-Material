// Link-Cut-Tree模板，支持路径查询、路径修改、link、cut、不支持子树操作。
//MaxNode 节点数
//用的时候在外面对输入树的每个节点i调用一下pt[i].Init()即可。
struct node {
	int v, f, ch[2], s;
	node() {}
	void Init(int _v, int _f) {
		v = _v; f = _f;
		ch[0] = ch[1] = 0;
		s = 1;
	}
}pt[MaxNode];

struct LCT {
	struct node{
		int f,ch[2],sum,v,s; bool rev,isroot;
		void Make_Rev() {
			rev = !rev; swap(ch[0],ch[1]);
		}
		void Init(int _v, int _f) {
			f = _f; ch[0] = ch[1] = 0; isroot = true; rev = false;
			sum = v = _v;
			s = 1;
		}
	}pt[MaxNode];
	void push(int t) {
		if (pt[t].rev) {
			if (pt[t].ch[0]) pt[pt[t].ch[0]].Make_Rev();
			if (pt[t].ch[1]) pt[pt[t].ch[1]].Make_Rev();
			pt[t].rev = false;
		}
	}
	void updata(int t) {
		pt[t].s = pt[pt[t].ch[0]].s + pt[pt[t].ch[1]].s + 1;
		pt[t].sum = pt[pt[t].ch[0]].sum + pt[pt[t].ch[1]].sum + pt[t].v;
	}
	void zig(int x,bool w) {
		int y = pt[x].f; if (pt[y].isroot) { pt[y].isroot = false; pt[x].isroot = true; }
		push(y); push(x);
		pt[y].ch[!w] = pt[x].ch[w]; if (pt[x].ch[w]) pt[pt[x].ch[w]].f = y;
		pt[x].f = pt[y].f; if (!pt[x].isroot) pt[pt[y].f].ch[y == pt[pt[y].f].ch[1]] = x;
		pt[x].ch[w] = y; pt[y].f = x; updata(y);
	}
	void splay(int x) {
		while (!pt[x].isroot) {
			push(x);
			if (pt[pt[x].f].isroot) zig(x, x == pt[pt[x].f].ch[0]);
			else { 
				int y = pt[x].f, z = pt[y].f;
				if (y == pt[z].ch[0]) if (x == pt[y].ch[0]) {zig(y,1); zig(x,1); } else {zig(x,0); zig(x,1); }
					else if (x == pt[y].ch[0]) { zig(x,1); zig(x,0); } else {zig(y,0); zig(x,0); }
			}
		} updata(x);
	}
	int  access(int x,int cas) { // -1 for reverse
		int p = 0, q = x, ret = 0;
		while (q) {
			splay(q); push(q);
			if (pt[q].f == 0) {
				ret = pt[pt[q].ch[1]].sum + pt[p].sum;
				if (pt[q].ch[1]) {
					int t = pt[q].ch[1];	
					if (!p) {
						while (pt[t].ch[0]) t = pt[t].ch[0];
						ret -= pt[t].v;
					}
				}
				if (p) {
					int t = p;
					if (!pt[q].ch[1]) {
						while (pt[t].ch[0]) t = pt[t].ch[0];
						ret -= pt[t].v;
					}
				}
			}
			pt[pt[q].ch[1]].isroot = true; pt[p].isroot = false;
			pt[q].ch[1] = p; updata(q); p = q; q = pt[q].f;
		}
		splay(p);
		if (cas == 0) ret = pt[p].s;
		if (cas == -1) pt[p].Make_Rev();
		return ret;
	}
	int root(int x) {
		access(x,0);
		splay(x);
		while (pt[x].ch[0]) x = pt[x].ch[0];
		return x;
	}
	void Link(int x,int y) {
		access(x, -1); splay(x); pt[x].f = y;
	}
	bool Son(int x,int y) {
		access(x,0); splay(y); 
		return pt[y].ch[1] == x;
	}  
	void Cut(int x,int y) {
		if (Son(x,y)) swap(x,y);
		access(y,0); splay(x); pt[y].isroot = true; pt[x].ch[1] = 0; pt[y].f = 0;
	}
}Tree;
