// MaxN 节点数
// 支持link cut 修改点权，查询所在联通块最大值
// 简单版的维护子树lct，不要随便改奇怪的地方。

struct node {
	int f,ch[2],Max; bool isroot,rev;
	multiset<int> Heap;
	void Init(int _v,int _f) {
		isroot = true; rev = false ;
		ch[0] = ch[1] = 0; f = _f;
		Heap.clear(); Heap.insert(_v); Max = _v;
	}
	void Make_Rev() {
		swap(ch[0],ch[1]); rev ^= 1;
	}	
}pt[MaxN];

struct LCT {
	void push(int t) {
		if (pt[t].rev) {
			if (pt[t].ch[0]) pt[pt[t].ch[0]].Make_Rev();
			if (pt[t].ch[1]) pt[pt[t].ch[1]].Make_Rev();
			pt[t].rev = 0;
		}
	}
	void update(int t) {
		if (!t) while(1);
		pt[t].Max = max(*pt[t].Heap.rbegin(),max(pt[pt[t].ch[0]].Max,pt[pt[t].ch[1]].Max));
	}
	void zig(int x,bool w){
		int y = pt[x].f; push(y); push(x); 
		if(pt[y].isroot) {pt[y].isroot = false; pt[x].isroot = true; }
		push(y); push(x);
		pt[y].ch[!w] = pt[x].ch[w]; if(pt[x].ch[w]) pt[pt[x].ch[w]].f = y;
		pt[x].f = pt[y].f; if(!pt[x].isroot) pt[pt[y].f].ch[y == pt[pt[y].f].ch[1]] = x;
		pt[x].ch[w] = y; pt[y].f = x; update(y);
	}
	void splay(int x){
		while(!pt[x].isroot){
			push(x);
			if(pt[pt[x].f].isroot) zig(x,x == pt[pt[x].f].ch[0]);
			else { int y = pt[x].f, z = pt[y].f;
				if(y == pt[z].ch[0])
					if(x == pt[y].ch[0]){ zig(y,1); zig(x,1); }
					else { zig(x,0); zig(x,1); }
				else if(x == pt[y].ch[0]){ zig(x,1); zig(x,0); }
					else { zig(y,0); zig(x,0); }
			}
		}
		update(x);
	}
	int access(int x){//1 询问 2 Reverse 0 没事 
		int p = 0,q = x; PII ret = MP(0,0);
		while (q) {
			splay(q); push(q);
			if (pt[q].ch[1]) {
				pt[pt[q].ch[1]].isroot = true; pt[q].Heap.insert(pt[pt[q].ch[1]].Max);
			}
			if (p) {
				if (pt[q].Heap.find(pt[p].Max) == pt[q].Heap.end()) {
					int z = q;
				}
				pt[p].isroot = false; pt[q].Heap.erase(pt[q].Heap.find(pt[p].Max));
			}
			pt[q].ch[1] = p; update(q);
			p = q; q = pt[q].f;
		}
		return 0;
	}
	int Find(int p){
		access(p);splay(p);
		int t = p; while(pt[t].ch[0]) t = pt[t].ch[0];
		return t;
	}
	void Link(int x,int y){//x儿子 y父亲
		if(x==y)return;
		access(x); access(y);
		pt[x].f = y; pt[y].Heap.insert(pt[x].Max);
		update(y);
	}
	bool Son(int x,int y){//返回x是y的儿子
		access(y); splay(x); return (pt[x].f == y);
	}
	void Cut(int x,int y){
		if(!Son(x,y)) swap(x,y);
		if(x==y)return;
		//pt[y].Heap.erase(pt[y].Heap.find(pt[x].Max));
		access(x); splay(y);
		pt[y].ch[1] = 0; update(y);
		pt[x].f = 0; pt[x].isroot = true;
	}
}DTree;