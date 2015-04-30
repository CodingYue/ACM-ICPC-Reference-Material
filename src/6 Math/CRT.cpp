<TeX>lcm是mod的那个数，FACTOR是因子。只保证对于Square-Free Number的正确性。</TeX>
int ans = 0;
int lcm = 999911658;
for(int i = 0;i < 4;i++) {
	int t = lcm/FACTOR[i];
	 
	int x,y,d;
	exgcd(t,FACTOR[i],d,x,y);
	x = (ll)(x%lcm+lcm)%lcm*t*R[i]%lcm;
	ans = (ans+x)%lcm;
}
