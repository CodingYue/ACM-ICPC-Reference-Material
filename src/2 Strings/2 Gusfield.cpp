<TeX> $z_i$ = lcp(text+i,pattern) </TeX>
int z_pat[MAXLEN] = {0};
int zFunction(int* z,char* text,char* pat,int textLen=-1,int patLen=-1) {
	if(textLen == -1) textLen = strlen(text);
	if(patLen == -1) patLen = strlen(pat);
	
	int self = (text == pat && textLen == patLen);
	if(!self) zFunction(z_pat,pat,pat,patLen,patLen);
	else z[0] = patLen;
	
	int farfrom = 0;
	int far = self; // self->[farfrom,far) else [farfrom,far]
	for(int i = self;i < textLen;i++)
		if(i+z_pat[i-farfrom] >= far) {
			int x = max(far,i);
			while(x < textLen && x-i < patLen && text[x] == pat[x-i]) x++;
			z[i] = x-i;
			if(i < x) { farfrom = i; far = x; }
		}
		else z[i] = z_pat[i-farfrom];
	return 0;
}
