<TeX>需要改成持久化的话每次修改的时候新建节点即可，然后去掉对fa的维护即可。必要的情况下在newNode里面加上GC。</TeX>
struct TNODE
{
	int val,rd,size;
	TNODE* left,*right,*fa;

	inline int update()
	{
		size = 1;
		if(left) { size += left->size; left->fa = this; }
		if(right) { size += right->size; right->fa = this; }
		fa = NULL;
		return 0;
	}
};
typedef pair<TNODE*,TNODE*> ptt;
TNODE TPool[233333];
TNODE* TPTop = TPool;

inline int real_rand() { return ((rand()&32767)<<15)^rand(); }
TNODE* newNode(int val,TNODE* left=NULL,TNODE* right=NULL)
{
	TNODE* result = TPTop++;
	result->val = val; result->rd = real_rand(); result->left = left; result->right = right; result->fa = NULL;
	result->update();
	return result;
}

TNODE* Merge(TNODE* t1,TNODE* t2)
{
	if(!t1) return t2;
	if(!t2) return t1;
	if(t1->rd <= t2->rd) { t1->right = Merge(t1->right,t2); t1->update(); return t1; }
	else { t2->left = Merge(t1,t2->left); t2->update(); return t2; }
}

ptt Split(TNODE* x,int pos)
{
	if(pos == 0) return ptt(NULL,x);
	if(pos == x->size) return ptt(x,NULL);

	int lsize = x->left ? x->left->size : 0;
	int rsize = x->right ? x->right->size : 0;
	if(lsize == pos)
	{
		TNODE* oleft = x->left;
		if(x->left) x->left->update();
		x->left = NULL;
		x->update();
		return ptt(oleft,x);
	}
	if(pos < lsize)
	{
		ptt st = Split(x->left,pos);
		x->left = st.second; x->update(); if(st.first) st.first->update();
		return ptt(st.first,x);
	}
	else
	{
		ptt st = Split(x->right,pos-lsize-1);
		x->right = st.first; x->update(); if(st.second) st.second->update();
		return ptt(x,st.second);
	}
}

inline int Rank(TNODE* x)
{
	int ans = x->left ? x->left->size : 0;
	while(x->fa)
	{
		if(x == x->fa->right) ans += (x->fa->left ? x->fa->left->size : 0) + 1;
		x = x->fa;
	}
	return ans;
}
