<TeX>神奇的东西，所谓的Palindrome Tree其实是每个点表示了一个回文子串，而边则是表示在两侧同时添加上这个字母可以得到的新回文子串。
从点u到点w的suffix link表示w是u的所有不是u本身的后缀中最长的回文子串。
这个所谓的``Tree''实际上有两个根。一个表示$-1$长度的串，用于表示只有一个字母的新回文串的产生，一个表示空串。两个根的suffix link都指向-1根。
有编号大的点就是拓扑序小的点这个性质。

一些应用：
\begin{enumerate}
\item 统计加入一个字母的时候增加了多少个新的（不同的）回文串：看看加入字母的时候多出来几个点就行了。答案只可能是0或1。
\item 计算回文子串个数：这个Manacher可以做，但是用Palindrome Tree的话更有趣。注意到Suffix Link关系是棵树（两个根两棵树），对每个点维护它到根的连接数，然后对于新加入的点加上它的连接数即可（考虑Suffix Link关系的意义，显然）。
\item 计算每个不同的子回文串的出现次数：基本同上，注意到对于新加入的点它是对本身和Suffix Link上的所有点贡献了1的答案，于是上推一遍即可。
\end{enumerate}

$O(n \log \sum)$，可以假装自己是线性的，像SAM一样。</TeX>
template<int MAXN, int SIGMA> class PalindromeTree {
public:
	struct TNODE {
		int len;
		TNODE* suffLink, *child[SIGMA];
		
		/* Extra fields */
		// int cnt;
		/* ------------ */
	};

	char text[MAXN]; int textLen;
	TNODE NPool[MAXN+2];
	TNODE* NPTop, *Last, *Root_Guard, *Root_Empty;

	PalindromeTree() { reset(); }
	int reset() {
		NPTop = NPool;
		Root_Guard = NPTop++; Root_Empty = NPTop++;
		memset(Root_Guard,0,sizeof(TNODE));
		memset(Root_Empty,0,sizeof(TNODE));
		Root_Guard->len = -1; Root_Empty->len = 0;
		Root_Guard->suffLink = Root_Empty->suffLink = Root_Guard;
		Last = Root_Empty;
		return 0;
	}

	// return 0 or 1, indicating new (distinct) palindrome substring count.
	int feed(int ch) {
		text[textLen++] = ch;

		TNODE* cur = Last;
		while(textLen-1-1-cur->len < 0 || text[textLen-1-1-cur->len] != ch) cur = cur->suffLink;
		if(cur->child[ch]) { Last = cur->child[ch]; return 0; }

		TNODE* x = NPTop++;
		memset(x,0,sizeof(TNODE));
		Last = x;
		x->len = cur->len + 2;
		cur->child[ch] = x;
		if(x->len == 1) { // from -1 root
			x->suffLink = Root_Empty;
		} else {
			cur = cur->suffLink;
			while(textLen-1-1-cur->len < 0 || text[textLen-1-1-cur->len] != ch)
				cur = cur->suffLink;
			x->suffLink = cur->child[ch];
		}
		// maintain additional field here.
		return 1;
	}
};
