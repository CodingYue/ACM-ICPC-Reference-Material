<TeX> 大部分应用基于一个性质：fail指向与当前串的后缀相等的前缀最长的节点。
 另外可以模仿匹配过程在Trie上DP进行统计。
 Build a Trie then run the code below. </TeX>
TNODE* Queue[66666];
int build_ac_automaton() {
	int front = 0; int end = 0;
	Queue[end++] = Root;
	while(front != end) {
		TNODE* x = Queue[front++];
		for(int i = 0;i < 26;i++) {
			if(x->Child[i]) {
				x->Child[i]->Fail = x->Fail?x->Fail->Child[i]:Root;
				// Spread additional info here for trie graph
				//x->Child[i]->Readable |= x->Child[i]->Fail->Readable; 
				Queue[end++] = x->Child[i];
			}
			else x->Child[i] = x->Fail?x->Fail->Child[i]:Root; // trie graph
		}
	}
	return 0;
}
