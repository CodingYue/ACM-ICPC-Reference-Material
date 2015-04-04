SAMNODE* Root,*Last; // take care, init them
int append_char(int ch) {
	SAMNODE* x = Last, t = SPTop++;
	t->len = x->len+1;
	for(;x && !x->child[ch];x = x->fa) x->child[ch] = t;
	if(!x) t->fa = Root;
	else {
		SAMNODE* bro = x->child[ch];
		if(x->len+1 == bro->len) t->fa = bro; // actually it's fa.
		else {
			SAMNODE* nfa = SPTop++;
			nfa[0] = bro[0];
			nfa->len = x->len+1;
			bro->fa = t->fa = nfa;

			for(;x && x->child[ch] == bro;x = x->fa) x->child[ch] = nfa;
		}
	}
	Last = t;
	return 0;
}

// SAM::Match //
SAMNODE* x = Root;
int mlen = 0;
for(int j = 0;j < len;j++) {
	int ch = Text[j];
	/*// 强制后撤一个字符，部分情况下可能有用
	if(mlen == qlen) {
		mlen--;
		while(mlen <= x->fa->len) x = x->fa;
	} */
	if(x->child[ch]) { mlen++; x = x->child[ch]; }
	else {
		while(x && !x->child[ch]) x = x->fa;
		if(!x) {
			mlen = 0;
			x = Root;
		} else {
			mlen = x->len+1;
			x = x->child[ch];
		}
	}
	Match[j] = mlen;
} // End of SAM::Match //

// 基排方便上推一些东西，比如出现次数 //
SAMNODE* order[2222222];
int lencnt[1111111];
int post_build(int len) {
	for(SAMNODE* cur = SPool;cur < SPTop;cur++) lencnt[cur->len]++;
	for(int i = 1;i <= len;i++) lencnt[i] += lencnt[i-1];
	int ndcnt = lencnt[len];
	for(SAMNODE* cur = SPTop-1;cur >= SPool;cur--) order[--lencnt[cur->len]] = cur;
	for(int i = ndcnt-1;i >= 0;i--) {
		// 此处上推
		if(order[i]->fa) order[i]->fa->cnt += order[i]->cnt;
	}
	return 0;
}
