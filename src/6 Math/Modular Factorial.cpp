<TeX>对于素数p，求$n!$在可以表示成$n! = ap^k$时的$a$的值。 $O(p \log n)$</TeX>

int modFact(int n,int p)
{
	int ans = 1;
	while(n > 0)
	{
		for(int i = 1, m = n % p;i <= m;i++) ans = (ans * i) % p;
		if((n /= p) % 2 > 0) res = p - res;
	}
	return res;
}
