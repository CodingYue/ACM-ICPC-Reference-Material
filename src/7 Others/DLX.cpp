const int MAXINT = 0x7FFFFFFF;

struct DLXNODE
{
	union
	{
		int S;
		DLXNODE* C;
	};
	int Row;
	DLXNODE *U,*D,*L,*R;
};

DLXNODE H;
DLXNODE NodePool[10000] = {0};
int PoolTop = 0;

DLXNODE* node_alloc()
{
	memset(&NodePool[PoolTop],0,sizeof(DLXNODE));
	return &NodePool[PoolTop++];
}

int ans[100] = {0}; // 9x9

int remove(DLXNODE* c)
{
	c->L->R = c->R;
	c->R->L = c->L;

	for(DLXNODE* i = c->D;i != c;i = i->D)
	{
		for(DLXNODE* j = i->R;j != i;j = j->R)
		{
			j->U->D = j->D;
			j->D->U = j->U;
			j->C->S--;
		}
	}
	return 0;
}

int resume(DLXNODE* c)
{
	for(DLXNODE* i = c->D;i != c;i = i->D)
	{
		for(DLXNODE* j = i->L;j != i;j = j->L)
		{
			j->U->D = j;
			j->D->U = j;
			j->C->S++;
		}
	}

	c->L->R = c;
	c->R->L = c;
	return 0;
}

bool dfs(int k)
{
	if(H.R == &H)
	{
		// found! add custom handler here.
		return true;
	}

	DLXNODE* tc = NULL;
	int ts = MAXINT;
	for(DLXNODE* i = H.R;i != &H;i = i->R)
	{
		if(i->S < ts)
		{
			ts = i->S;
			tc = i;
		}
	}
	if(ts == MAXINT) return true;
	remove(tc);
	for(DLXNODE* i = tc->U;i != tc;i = i->U)
	{
		ans[k] = i->Row; // store state here
		for(DLXNODE* j = i->R;j != i;j = j->R)
		{
			remove(j->C);
		}
		if(dfs(k+1)) return true;
		for(DLXNODE* j = i->L;j != i;j = j->L)
		{
			resume(j->C);
		}
	}
	resume(tc);
	return false;
}

DLXNODE* insert_to_col(DLXNODE* c,int RowNo,DLXNODE* rl)
{
	DLXNODE* node = node_alloc();
	// c->U is last node
	node->U = c->U;
	node->D = c;
	if(!rl) node->L = node->R = node;
	else
	{
		node->L = rl;
		node->R = rl->R;
		rl->R->L = node;
		rl->R = node;
	}
	node->C = c;
	node->Row = RowNo;
	c->S++;
	c->U->D = node;
	c->U = node;
	return node;
}

// 对应 9x9 数独的建图
int main(void)
{
	char Scene[100] = {0};
	while(scanf("%s",Scene) != EOF && strcmp(Scene,"end"))
	{
		PoolTop = 0;
		memset(ans,0,sizeof(ans));

		H.L = H.R = H.U = H.D = &H;
		DLXNODE* cFind[324] = {0};
		DLXNODE* last = &H;
		for(int i = 0;i < 324;i++)
		{
			DLXNODE* tn = node_alloc();
			cFind[i] = tn;
			tn->S = 0;
			tn->D = tn->U = tn;
			tn->L = last; tn->R = last->R;
			last->R->L = tn; last->R = tn;
			last = tn;
		}
		for(int i = 0;i < 9;i++)
		{
			for(int j = 0;j < 9;j++)
			{
				int s = 1; int e = 9;
				if(Scene[i*9+j] != '.') s = e = Scene[i*9+j]-'0';
				for(int k = s;k <= e;k++)
				{
					int b = (i/3)*3+j/3;

					int RowNo = i*9*9+j*9+k-1;

					DLXNODE* ln = NULL;
					ln = insert_to_col(cFind[i*9+j],RowNo,ln);
					ln = insert_to_col(cFind[81+i*9+k-1],RowNo,ln);
					ln = insert_to_col(cFind[162+j*9+k-1],RowNo,ln);
					ln = insert_to_col(cFind[243+b*9+k-1],RowNo,ln);
				}
			}
		}
		dfs(0);
		for(int i = 0;i < 81;i++)
		{
			int RNo = ans[i];
			int k = RNo % 9 + 1;
			int j = RNo / 9 % 9;
			int r = RNo / 81;
			Scene[r*9+j] = '0' + k;
		}
		printf("%s\n",Scene);
	}
	return 0;
}

