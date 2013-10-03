int Kth(int k)
{
	int cnt = 0;
	int ans = 0;
	for(int p = (1<<logcnt);p > 0;p >>= 1)
	{
		ans += p;
		if(ans > scorecnt || cnt+BIT[ans] >= k) ans -= p;
		else cnt += BIT[ans];
	}
	return ans+1-1;
}
