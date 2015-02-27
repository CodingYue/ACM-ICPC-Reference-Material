/* return x*y%mod. no overflow if x,y < mod
 * remove 'i' in "idiv"/"imul" if change to unsigned*/
inline int mulmod(int x,int y,int mod)
{
	int ans = 0;
	__asm__ (
		"movl %1,%%eax\n imull %2\n idivl %3\n"
		:"=d"(ans):"m"(x),"m"(y),"m"(mod):"%eax"
	);
	return ans;
}
