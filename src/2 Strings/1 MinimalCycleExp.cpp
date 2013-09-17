<TeX> 返回 text 的所有循环同构中字典序最小的起始位置。O(n) </TeX>
int MinimalRep(char* text,int len=-1)
{
	if(len == -1) len = strlen(text);

	int i = 0;
	int j = 1;
	while(i < len && j < len)
	{
		int k = 0;
		while(k < len && text[(i+k)%len] == text[(j+k)%len]) k++;
		if(k >= len) break;

		if(text[(i+k)%len] > text[(j+k)%len]) i = max(i+k+1,j+1);
		else j = max(i+1,j+k+1);
	}
	return min(i,j);
}
