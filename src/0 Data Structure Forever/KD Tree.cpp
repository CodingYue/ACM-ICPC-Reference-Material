<TeX>如果被卡可以考虑写上 minx,maxx,miny,maxy 维护矩形，修改 KDTree\_Build 加上对应的维护。</TeX>
struct POINT { int x,y,id; };
inline bool cmp_x(const POINT& a,const POINT& b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
inline bool cmp_y(const POINT& a,const POINT& b) { return a.y == b.y ? a.x < b.x : a.y < b.y; }

struct KDNODE
{
	POINT p;
//	int minx,maxx,miny,maxy;

	KDNODE* Child[2];
	KDNODE* fa;
};
KDNODE NPool[111111];
KDNODE* NPTop = NPool;
KDNODE* Root;

inline KDNODE* AllocNode()
{
	memset(NPTop,0,sizeof(KDNODE));
	return NPTop++;
}

inline ll PDist(const POINT& a,const POINT& b) { return sqr((ll)(a.x-b.x))+sqr((ll)(a.y-b.y)); }

POINT pnt[111111];

KDNODE* KDTree_Build(int l,int r,int depth=0)
{
	if(l >= r) return NULL;

	if(depth&1) sort(pnt+l,pnt+r,cmp_y);
	else sort(pnt+l,pnt+r,cmp_x);

	int mid = (l+r)/2;
	KDNODE* t = AllocNode();
	
	t->Child[0] = KDTree_Build(l,mid,depth+1);
	t->Child[1] = KDTree_Build(mid+1,r,depth+1);
	for(int i = 0;i < 2;i++)
		if(t->Child[i]) t->Child[i]->fa = t;

	return t;
}

int KDTree_Insert(KDNODE* cur,POINT& P,int depth=0)
{
	KDNODE* node = AllocNode(); node->p = P;
	while(cur)
	{
		if(cur->p.x == P.x && cur->p.y == P.y && cur->p.id == P.id) break;
		int dir = 0;
		if(depth&1) dir = cmp_y(x->p,P);
		else dir = cmp_x(x->p,P);
		if(!cur->Child[dir])
		{
			cur->Child[dir] = node;
			node->fa = cur;
			break;
		}
		else
		{
			cur = cur->Child[dir];
			depth++;
		}
	}
	return 0;
}

ll KDTree_Nearest(KDNODE* x,const POINT& q,int depth=0)
{
	KDNODE* troot = x->fa;
	int dir = 0;
	while(x)
	{
		if(depth&1) dir = cmp_y(x->p,q);
		else dir = cmp_x(x->p,q);

		if(!x->Child[dir]) break;
		x = x->Child[dir];
		depth++;
	}
	ll ans = ~0ULL>>1;
	while(x != troot)
	{
		ll tans = PDist(q,x->p);
		if(tans < ans) ans = tans;
		KDNODE* oside = x->Child[dir^1];
		if(oside)
		{
			ll ldis = 0;
			/*if(depth&1) ldis = min(sqr((ll)q.y-oside->miny),sqr((ll)q.y-oside->maxy));
			else ldis = min(sqr((ll)q.x-oside->minx),sqr((ll)q.x-oside->maxx));*/
			if(depth & 1) ldis = sqr<ll>(x->p.y-q.y);
			else ldis = sqr<ll>(x->p.x-q.x);
			if(ldis < ans)
			{
				tans = KDTree_Nearest(oside,q,depth+1);
				if(tans && tans < ans) ans = tans;
			}
		}

		if(x->fa && x == x->fa->Child[0]) dir = 0;
		else dir = 1;
		x = x->fa;
		depth--;
	}
	return ans;
}
