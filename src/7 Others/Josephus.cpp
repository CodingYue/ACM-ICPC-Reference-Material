<TeX>约瑟夫环，避免有人无聊，某种奇怪的实现等等加上。</TeX>

int josephus(int n,int m,int k)
{
	int x = -1;
	for(int i = n - k + 1;i <= n;i++)
	{
		x = (x + m) % i;
	}
	return x;
}

int invJosephus(int n,int m,int x)
{
	for(int i = n;;i--)
	{
		if(x == i) return n-i;
		x = (x - m % i + i) % i;
	}
	assert(false);
}