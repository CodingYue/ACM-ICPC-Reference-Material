// Always call "IsPrime" unless you know what are you doing

int MillerRabin(ull a,ull n)
{
	if(n == 2) return 1;
	if(n == 1 || (n & 1) == 0) return 0;
	ull d = n-1;
	while((d & 1) == 0) d >>= 1;
	ull t = powmod(a,d,n);
	while(d != n-1 && t != 1 && t != n-1)
	{
		t = mulmod(t,t,n);
		d <<= 1;
	}
	return (t == n-1) || ((d & 1) == 1);
}

int LPrimes[] = {2,3,5,7,11,13,17,19,23};
int IsPrime(ull n)
{
	int result = 1;
	for(int i = 0;i < sizeof(LPrimes)/sizeof(int);i++)
	{
		if(LPrimes[i] >= n) break;
		result &= MillerRabin(LPrimes[i],n);
		if(!result) return result;
	}
	return result;
}
