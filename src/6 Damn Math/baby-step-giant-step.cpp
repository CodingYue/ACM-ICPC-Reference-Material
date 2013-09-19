namespace BSGS {
	#define MaxNode 1200007
	#define HMD 1000007
	struct Thash{
		PII has[MaxNode];int next[MaxNode],h[HMD],tot;
		void clr(){
			memset(h, 0, sizeof h);
		}
		void ins(int p,int pos){
			int vex = p % HMD;
			for(int z = h[vex]; z; z = next[z]) if(has[z].fi == p) return;
			has[++tot] = MP(p,pos); next[tot] = h[vex]; h[vex] = tot;
		}
		int  find(int p){
			if (p == 0) return -1;
			for(int z = h[p % HMD]; z; z = next[z]) if(has[z].fi == p) return has[z].se;
			return -1;
		}
	}Hash;
	void build(int y, int p){
		m = 700000; int now = 1;
		for (int i = 0; i <= m; ++i) {
			Hash.ins(now,i);
			now = (LL) now * y % p;
		}
	}
	int find(int y, int z, int p)
	{
		int D = fpow(y, m, p), now = 1;
		D = fpow(D, p - 2, p);
		for (int i = 0; i <= p / m + 1; ++i) {
			int t = Hash.find((long long)z * now % p);
			if (t + 1) return i * m + t;
			now=(long long) now * D % p;
		}
		return -1;
	}
};
