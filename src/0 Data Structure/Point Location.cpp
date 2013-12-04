<TeX>不掉精度的题可以试试，现在不太好用。自带持久化，改成非持久化小心写错。</TeX>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

template<typename T,typename HT>
class POINT2D_META
{
public:
	T x;
	T y;
	POINT2D_META() { x = y = 0; }
	POINT2D_META(T _x,T _y):x(_x),y(_y) { }
	inline POINT2D_META operator+(const POINT2D_META& b) const { return POINT2D_META(x+b.x,y+b.y); }
	inline POINT2D_META operator-(const POINT2D_META& b) const { return POINT2D_META(x-b.x,y-b.y); }
	inline HT operator*(const POINT2D_META& b) const { return (HT)x*b.y-(HT)b.x*y; }
	inline HT dot(const POINT2D_META& b) const { return (HT)x*b.x+(HT)y*b.y; }
	inline HT hypot2() const { return (HT)x*x+(HT)y*y; }
	inline T hypot() const { return ::hypot(x,y); }
	inline int read() { return scanf("%d %d",&x,&y); }
	// h-v order
	inline bool operator<(const POINT2D_META& b) const { return x == b.x ? y < b.y : x < b.x; }
	inline bool operator==(const POINT2D_META& b) const { return x == b.x && y == b.y; }
};
typedef POINT2D_META<int,ll> POINT;

class SEGMENT
{
public:
	static long double x;

	POINT l; POINT r;
	int which;
	int side;
	SEGMENT() {}
	SEGMENT(const POINT& _l,const POINT& _r,int which,int side):l(_l),r(_r),which(which),side(side) {if(l.x > r.x) swap(l,r); }
	long double evaluate() const { return (x-l.x)/((long double)r.x-l.x)*((long double)r.y-l.y)+l.y; }
	inline bool operator==(const SEGMENT& b) const { return side == b.side && which == b.which && l == b.l && r == b.r; } 
}; long double SEGMENT::x = 0.0; // dirty implementation

class TNODE
{
private:
	inline bool determineSide(int a,int b) { return rand() % (a+b) < a; }
public:
	SEGMENT val;
	int size,refCount;
	TNODE* left;
	TNODE* right;

	TNODE(const SEGMENT& val,TNODE* left,TNODE* right):val(val),left(left),right(right)
	{
		update();
		refCount = 0;
		if(left) left->refCount++;
		if(right) right->refCount++;
	}
	~TNODE()
	{
		if(left && --left->refCount <= 0) delete left;
		if(right && --right->refCount <= 0) delete right;
	}

	inline TNODE* ref() { if(this) refCount++; return this; }
	inline TNODE* deref() { if(this && --refCount <= 0) { delete this; return NULL; } return this; }

	inline TNODE* update()
	{
		size = (left ? left->size : 0) + 1 + (right ? right->size : 0);
		return this;
	}

	TNODE* merge(TNODE* q)
	{
		TNODE* p = this;
		if(!p) return q;
		if(!q) return p;
		if(determineSide(p->size,q->size)) return new TNODE(p->val,p->left,p->right->merge(q)); // as p
		return new TNODE(q->val,p->merge(q->left),q->right); // as q
	}

	typedef pair<TNODE*,TNODE*> ptt;
	ptt split(const SEGMENT& base) // split right after base, and erase base if found
	{
		if(!this) return ptt(NULL,NULL);
		if(base == val) return ptt(left, right); // erase base
		long double va = base.evaluate();
		long double vb = val.evaluate();
		if(va < vb)
		{
			ptt st = left->split(base);
			return ptt(st.first, new TNODE(val,st.second,right)); // as self
		}
		else
		{
			ptt st = right->split(base);
			return ptt(new TNODE(val,left,st.first), st.second); // as self
		}
	}

	TNODE* lower_bound(long double va)
	{
		if(!this) return NULL;
		long double vb = val.evaluate();
		if(fabs(vb-va) < 1e-8) return this; // no dup entry, no issue
		if(va > vb) return right ? right->lower_bound(va) : NULL;

		TNODE* ans = NULL;
		if(left) ans = left->lower_bound(va);
		if(!ans) ans = this;
		return ans;
	}

	TNODE* abit_smaller(long double va)
	{
		if(!this) return NULL;
		long double vb = val.evaluate();
		if(va <= vb+1e-8) return left ? left->abit_smaller(va) : NULL;

		TNODE* ans = NULL;
		if(right) ans = right->abit_smaller(va);
		if(!ans) ans = this;
		return ans;
	}
};typedef pair<TNODE*,TNODE*> ptt;

vector<POINT> polygon[111111];

struct EVENT
{
	int key,type;
	SEGMENT seg;
	EVENT() {}
	EVENT(int key,int type,const SEGMENT& seg):key(key),type(type),seg(seg) {}
	// warning: non-stable, do not use on set or similar things.
	inline bool operator<(const EVENT& b) const { return key != b.key ? key < b.key : type < b.type; }
};
EVENT events[666666];
int xpos[333333];
int xpcnt = 0;
TNODE* rootNode[333333];
int ShootingStar(int N)
{
	int evcnt = 0;
	for(int i = 0;i < N;i++)
	{
		int cnt = polygon[i].size();
		ll area = 0;
		for(int j = 0;j < cnt;j++) area += polygon[i][j] * polygon[i][(j+1)%cnt];
		if(area < 0) reverse(polygon[i].begin(),polygon[i].end());

		for(int j = 0;j < cnt;j++)
		{
			POINT now = polygon[i][j];
			POINT next = polygon[i][(j+1)%cnt];
			if(now.x == next.x) continue;

			int side = 1;
			if(now.x > next.x) { swap(now,next); side ^= 1; }
			events[evcnt++] = EVENT(now.x,1,SEGMENT(now,next,i,side));
			events[evcnt++] = EVENT(next.x,-1,SEGMENT(now,next,i,side));
		}
	}
	sort(events,events+evcnt);
	
	int xi = 0;
	for(int i = 0;i < evcnt;i++) if(!i || events[i].key != events[i-1].key) xpos[xpcnt++] = events[i].key;
	for(int i = 0;i < evcnt;)
	{
		int p = 0;
		for(p = i;p < evcnt && events[p].key == xpos[xi];p++)
		{
			if(events[p].type == -1)
			{
				SEGMENT::x = ((long double)xpos[xi-1]+xpos[xi])/2.0;
				TNODE* orig = rootNode[xi];
				ptt part = rootNode[xi]->split(events[p].seg); part.first->ref(); part.second->ref();
				rootNode[xi] = part.first->merge(part.second)->ref();
				part.first->deref(); part.second->deref(); orig->deref();
			}
			else if(events[p].type == 1)
			{
				SEGMENT::x = ((long double)xpos[xi+1]+xpos[xi])/2.0;
				TNODE* orig = rootNode[xi];
				ptt part = rootNode[xi]->split(events[p].seg); part.first->ref(); part.second->ref();
				TNODE* temp = part.first->merge(new TNODE(events[p].seg,NULL,NULL))->ref();
				rootNode[xi] = temp->merge(part.second)->ref();
				part.first->deref(); part.second->deref(); temp->deref(); orig->deref();
			}
		}
		rootNode[xi+1] = rootNode[xi]->ref();
		i = p; xi++;
	}
	return 0;
}

map<pii, int> vertexBelong;
int Memo(TNODE* root,const POINT& target)
{
	SEGMENT::x = target.x;
	TNODE* l = root->abit_smaller(target.y);
	TNODE* r = root->lower_bound(target.y);
	if(r && ((l && l->val.which == r->val.which && l->val.side == 1 && r->val.side == 0) || 
		fabs(r->val.evaluate()-target.y) < 1e-8)) return r->val.which+1;
	return -1;
}
int Marisa(const POINT& target)
{
	if(target.x > xpos[xpcnt-1] || target.x < xpos[0]) return -1;
	auto it = vertexBelong.find(pii(target.x,target.y));
	if(it != vertexBelong.end()) return it->second+1;

	int tx = max(0,lower_bound(xpos,xpos+xpcnt,target.x)-xpos-1);
	int ans = Memo(rootNode[tx],target);
	if(ans == -1 && tx+1 < xpcnt && xpos[tx+1] == target.x) ans = Memo(rootNode[tx+1],target);
	return ans;
}

int main(void)
{
	int N = 0;
	scanf("%d",&N);

	for(int i = 0;i < N;i++)
	{
		int cnt = 0;
		scanf("%d",&cnt);
		for(int j = 0;j < cnt;j++)
		{
			POINT cur; cur.read();
			polygon[i].push_back(cur);
			vertexBelong.insert(make_pair(pii(cur.x,cur.y),i));
		}
	}

	ShootingStar(N);

	int Q = 0;
	scanf("%d",&Q);
	while(Q--)
	{
		POINT target; target.read();
		printf("%d\n",Marisa(target));
		fflush(stdout);
	}
	return 0;
}
