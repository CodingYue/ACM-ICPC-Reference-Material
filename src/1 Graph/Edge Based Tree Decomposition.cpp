//边分治模板
//用的时候需要打上如上define..或者自行展开
//连读入也带上了，写的时候填空即可。（有空再补封装的好点的吧。。）
using namespace std;
#define For(i,l,r) for (int i = l; i <= r; ++i)
#define Cor(i,l,r) for (int i = l; i >= r; --i)
#define Fill(a,b) memset(a,b,sizeof(a))
#define FI first
#define SE second
#define MP make_pair
#define PII pair<int,int>
#define flt double
#define INF (0x3f3f3f3f)
#define MaxN 1020304
#define MaxNode 1020304
#define MD 1000000007

int v[MaxN], next[MaxN], h[MaxN], tot, w[MaxN];
void add(int b, int e, int wei) {
	v[++tot] = e; next[tot] = h[b]; h[b] = tot;
	v[++tot] = b; next[tot] = h[e]; h[e] = tot;
	w[tot] = w[tot - 1] = wei;
}

int vis[MaxN];
struct Edge {
	int b, e, wei;
	Edge() {}
	Edge(int _b, int _e, int _wei) : b(_b), e(_e), wei(_wei) {}
}E[MaxN];

int numE;
void add2(int b, int e, int wei) {
	E[++numE] = Edge(b,e,wei);
}

int nowNodes;
PII build(int l, int r, int *a, int *b) {
	if (l == r) return MP(a[l], b[l]);
	int tmp = ++nowNodes, mid = l + r >> 1;
	PII left = build(l,mid,a,b), right = build(mid+1,r,a,b);
	add2(tmp, left.FI, left.SE);
	add2(tmp, right.FI, right.SE);
	return MP(tmp, 0);
}

int n;
int id, q[MaxN], fa[MaxN], del[MaxN], s[MaxN], val[MaxN];
long long d[MaxN];
pair<long long, int> A[MaxN];
long long B[MaxN];
void tree_dc(int vex) {
	int hd = 0, tl = 1;
	vis[q[1] = vex] = ++id; fa[vex] = 0;
	while (hd < tl) {
		int vex = q[++hd];
		for (int z = h[vex]; z; z = next[z]) if (vis[v[z]] != id && !del[z]) {
			// remember to delete Edges
			vis[q[++tl] = v[z]] = id;
			fa[v[z]] = vex;
		}
	}
	if (tl == 1) {

		// boundary works.

		return ;
	}
	int Min = tl;
	int a,b;
	for (int i = tl; i >= 1; --i) {
		int vex = q[i];
		s[vex] = 1;
		for (int z = h[vex]; z; z = next[z]) if (vis[v[z]] == id && !del[z] && v[z] != fa[vex]) {
			s[vex] += s[v[z]];
		}
		int this_edge = max(s[vex], tl - s[vex]);
		if (this_edge < Min) {
			Min = this_edge; 
			a = vex; b = fa[vex];
		}
	}

	int tpweight;
	for (int z = h[a]; z; z = next[z]) if (v[z] == b) del[z] = true, tpweight = w[z];
	for (int z = h[b]; z; z = next[z]) if (v[z] == a) del[z] = true;// delete edge;

	For(TIME,0,1) {

		// do your work.

		swap(a,b);
	}

	tree_dc(a);
	tree_dc(b);
}

int cnode[MaxN], cwei[MaxN];
int main() {
	while (scanf("%d", &n) != EOF)	{

		// input
		memset(h,0,sizeof(h[0]) * (n + 10));
		tot = 0;
		For(i,1,n - 1) {
			int b,e,wei;
			scanf("%d%d%d", &b, &e, &wei);
			add(b,e,wei * 100001);
		}

		//rebuild the tree
		int hd = 0, tl = 1;
		memset(vis, 0, sizeof(vis[0]) * (n + 10));
		vis[q[1] = 1] = true;
		numE = 0; nowNodes = n;
		while (hd < tl) {
			int vex = q[++hd];
			int Tot = 0;
			for (int z = h[vex]; z; z = next[z]) if (!vis[v[z]]) {
				cnode[++Tot] = v[z]; cwei[Tot] = w[z];
				vis[q[++tl] = v[z]] = true;
			}
			if (Tot == 0) continue ;
			pair<int,int> res = build(1, Tot, cnode, cwei);
			add2(vex, res.FI, res.SE);
		} // rebuild the tree to reduce maximum-node-degree

		
		For(i,1,nowNodes) val[i] = (i <= n);//mark all nodes in the original tree

		n = nowNodes;
		memset(h,0,sizeof(h[0]) * (n + 10));
		tot = 0;
		For(i,1,numE) add(E[i].b, E[i].e, E[i].wei);

		memset(del, 0, sizeof(del[0]) * (tot + 10));
		memset(vis, 0, sizeof(vis[0]) * (n + 10));
		id = 0;
		tree_dc(1);

	}
	return 0;
}

