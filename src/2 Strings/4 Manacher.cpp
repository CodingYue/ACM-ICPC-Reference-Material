<TeX>$rad_i$ 为以 i/2 为中心向两端延伸的最长回文长度。
使用 rad 时注意是按照 ab->aabb 的 Pattern 填充过的，值二倍了。
返回值为 Text 串中的最长回文长度，不需要除以 2 。</TeX>
int rad[2222222];
int Manacher(char* Text,int len)
{
	len *= 2;
	
	int k = 0;
	for(int i = 0,j = 0;i < len;i += k,j = max(j-k,0))
	{
		while((i-j)/2 >= 0 && (i+j+1)/2 < len && Text[(i-j)/2] == Text[(i+j+1)/2]) j++;
		rad[i] = j;
		for(k = 1;i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k;k++)
			rad[i+k] = min(rad[i-k],rad[i]-k);
	}
	return *max_element(rad,rad+len);
}
