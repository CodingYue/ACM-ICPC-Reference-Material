<TeX>在线Manacher，支持尾部添加字母操作，这里的奇偶回文是分开维护的，而不是扩充一倍解决。maxPal是获取最长回文。</TeX>
template<int delta> class ManacherBase {
private:
	static const int MAXN=1e5+1;
	int r[MAXN]; char s[MAXN];
	int mid,n,i;
public:
	ManacherBase():mid(0),i(0),n(1) {
		memset(r,-1,sizeof(int)*MAXN);
		s[0] = '$'; r[0] = 0;
	}
	int get(int pos) {
		pos++;
		if(pos <= mid) return r[pos];
		else return min(r[mid - (pos - mid)], n - pos - 1);
	}
	void addLetter(char c) {
		s[n] = s[n+1] = c;

		while(s[i - r[i] - 1 + delta] != s[i + r[i] + 1]) r[++i] = get(i-1);
		r[mid=i]++; n++;
	}
	int maxPal() { return ( n - mid - 1 ) * 2 + 1 - delta; }
} ;

class Manacher {
private:
	ManacherBase<1> manacherEven;
	ManacherBase<0> manacherOdd;
public:
	void addLetter(char c) {
		manacherEven.addLetter(c);
		manacherOdd.addLetter(c);
	}
	int maxPal() { return max(manacherEven.maxPal(), manacherOdd.maxPal()); }
	int getRad(int type,int pos) {
		if(type) return manacherOdd.get(pos);
		else return manacherEven.get(pos);
	}
};