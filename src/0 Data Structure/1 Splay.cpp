<TeX>如果需要建初始树，记得 x->update()</TeX>
class SNode
{
public:
	int val;
	int size;
	bool rev;

	SNode* child[2];
	SNode* fa;

	int update()
	{
		pushdown();
		size = 1;
		for(int i = 0;i < 2;i++)
			if(child[i])
			{
				child[i]->pushdown();
				size += child[i]->size;
			}
		return 0;
	}
	int pushdown()
	{
		if(rev)
		{
			swap(child[0],child[1]);
			for(int i = 0;i < 2;i++)
				if(child[i]) child[i]->rev ^= 1;
			rev = false;
		}
		return 0;
	}
};

int Rotate(SNode* x,int dir)
{
	SNode* p = x->fa;
	p->pushdown();
	x->pushdown();

	p->child[dir] = x->child[dir^1];
	if(x->child[dir^1]) x->child[dir^1]->fa = p;
	x->child[dir^1] = p;

	x->fa = p->fa;
	if(!p->fa) Root = x;
	else if(p->fa->child[0] == p) p->fa->child[0] = x;
	else p->fa->child[1] = x;
	p->fa = x;
	p->update(); x->update();
	return 0;
}

SNode* Splay(SNode* x,SNode* Tar)
{
	while(x->fa != Tar)
	{
		int dir = 0;
		if(x->fa->child[0] == x) dir = 0;
		else dir = 1;
		if(x->fa->fa == Tar) Rotate(x,dir);
		else if(x->fa->fa->child[dir] == x->fa)
		{
			Rotate(x->fa,dir);
			Rotate(x,dir);
		} else {
			Rotate(x,dir);
			Rotate(x,dir^1);
		}
	}
	return x;
}

SNode* Select(SNode* x,int k)
{
	while(1)
	{
		x->pushdown();
		int xrank = 1;
		if(x->child[0]) xrank += x->child[0]->size;
		if(xrank == k) break;
		else if(k < xrank) x = x->child[0];
		else
		{
			x = x->child[1];
			k -= xrank;
		}
	}
	return x;
}
