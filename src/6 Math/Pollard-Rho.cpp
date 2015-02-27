ull PollardRho(ull n,int c) {
	ull x(2), y(2), d(1);
	while(d == 1) {
		x = (mulmod(x,x,n)+c)%n;
		y = (mulmod(y,y,n)+c)%n;
		y = (mulmod(y,y,n)+c)%n;

		if(x > y) d = gcd(x-y,n);
		else d = gcd(y-x,n);
	}
	return d;
}

// DO NOT CALL THIS WITH A PRIME!
ull Factorize(ull n) {
	ull d = n;
	while(d == n) d = PollardRho(n,rand()+1);
	return d;
}

// call sort if sorted results needed.
void FullFactorize(ull n, vector<ull>& result) {
	if(n%2 == 0) {
		result.push_back(2);
		while(n%2 == 0) n /= 2;
		return FullFactorize(n, result);
	}
	ull t = 0;
	while(n != 1 && !IsPrime(n)) {
		t = Factorize(n);
		int cdvc = result.size();
		if(!IsPrime(t)) FullFactorize(t, result);
		else result.push_back(t);
		for(int i = cdvc;i < result.size();i++) while(n % dv[i] == 0) n /= dv[i];
	}
	if(n != 1) result.push_back(n);
}
