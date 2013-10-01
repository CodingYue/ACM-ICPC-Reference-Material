ull PollardRho(ull n,int c)
{
	ull x = 2;
	ull y = 2;
	ull d = 1;
	while(d == 1)
	{
		x = (mulmod(x,x,n)+c)%n;
		y = (mulmod(y,y,n)+c)%n;
		y = (mulmod(y,y,n)+c)%n;

		if(x > y) d = gcd(x-y,n);
		else d = gcd(y-x,n);
	}
	return d;
}

// DO NOT CALL THIS WITH A PRIME!
ull Factorize(ull n)
{
	ull d = n;
	while(d == n) d = PollardRho(n,rand()+1);
	return d;
}

ull dv[111111];
int dvcnt = 0;

// call sort if sorted results needed.
ull FullFactorize(ull n)
{
	if(n%2 == 0)
	{
		dv[dvcnt++] = 2;
		while(n%2 == 0) n /= 2;
		return FullFactorize(n);
	}
	ull t = 0;
	while(n != 1 && !IsPrime(n))
	{
		t = Factorize(n);
		int cdvc = dvcnt;
		if(!IsPrime(t)) FullFactorize(t);
		else dv[dvcnt++] = t;
		for(int i = cdvc;i < dvcnt;i++)
		{
			while(n % dv[i] == 0) n /= dv[i];
		}
	}
	if(n != 1) dv[dvcnt++] = n;
	return 0;
}
