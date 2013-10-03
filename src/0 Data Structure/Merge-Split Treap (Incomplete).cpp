struct TNODE
{
	int val;
	int rd;
	int size;

	TNODE* left;
	TNODE* right;

	inline int update()
	{
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
		return 0;
	}
};

typedef pair<TNODE*,TNODE*> ptt;

stack<TNODE*> GCPool;
TNODE TPool[11111111];
TNODE* TPTop = TPool;

TNODE* newNode(int val,int rd,TNODE* left,TNODE* right)
{
	TNODE* result = NULL;
	if(GCPool.size()) { result = GCPool.top(); GCPool.pop(); }
	else result = TPTop++;
	result->val = val; result->rd = rd; result->left = left; result->right = right;
	result->update();
	return result;
}

TNODE* Merge(TNODE* t1,TNODE* t2)
{
	if(!t1) return t2;
	if(!t2) return t1;

	if(t1->rd <= t2->rd) return newNode(t1->val,t1->rd,t1->left,Merge(t1->right,t2));
	else return newNode(t2->val,t2->rd,Merge(t1,t2->left),t2->right);
}

// split after pos nodes
ptt Split(TNODE* x,int pos)
{
	if(pos == 0) return ptt(NULL,x);
	if(pos == x->size) return ptt(x,NULL);

	int lsize = x->left ? x->left->size : 0;
	int rsize = x->right ? x->right->size : 0;
	if(lsize == pos) return ptt(x->left,x->right);
	if(pos < lsize)
	{
		ptt st = Split(x->left,pos);
		return ptt(st.first,newNode(x->val,x->rd,st.second,x->right));
	}
	else
	{
		ptt st = Split(x->right,pos-lsize-1);
		return ptt(newNode(x->val,x->rd,x->left,st.first),st.second);
	}
}
