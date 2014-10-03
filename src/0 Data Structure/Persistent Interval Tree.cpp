<TeX>As elegant as possible.</TeX>

class SEGNODE {
public:
	SEGNODE() { memset(this,0,sizeof(SEGNODE)); maxval = -23333; }
	SEGNODE(SEGNODE* _orig) { if(_orig) memcpy(this,_orig,sizeof(SEGNODE)); else { memset(this,0,sizeof(SEGNODE)); maxval = -23333; } }
	
	SEGNODE *left, *right;
	int maxval;
	
	SEGNODE* dup() { return new SEGNODE(this); }
	
	SEGNODE* modify(int x,int val,int tl,int tr) {
		SEGNODE* self = dup();
		if(x == tl && tl == tr) {
			self->maxval = max(self->maxval,val);
			return self;
		}
		
		int mid = (tl+tr)/2;
		if(x <= mid) self->left = self->left->modify(x,val,tl,mid);
		else if(x > mid) self->right = self->right->modify(x,val,mid+1,tr);
		
		/* UPDATE */
		self->maxval = -23333;
		if(self->left) self->maxval = max(self->maxval,self->left->maxval);
		if(self->right) self->maxval = max(self->maxval,self->right->maxval);
		////////////
		return self;
	}
	
	int query(int l,int r,int tl,int tr) {
		if(!this) return -23333;
		if(l <= tl && tr <= r) return maxval;
		
		int mid = (tl+tr)/2;
		int ans = -23333;
		if(l <= mid) ans = max(ans,left->query(l,r,tl,mid));
		if(r > mid) ans = max(ans,right->query(l,r,mid+1,tr));
		return ans;
	}
};