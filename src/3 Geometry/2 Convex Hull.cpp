// P is input and Hull is output.
// return point count on hull
int Graham(POINT* P,POINT* Hull,int n)
{
	sort(P,P+n);
	int HTop = 0;
	for(int i = 0;i < n;i++)
	{
		// delete collinear points
		while(HTop > 1 && valsign((P[i]-Hull[HTop-2])*(Hull[HTop-1]-Hull[HTop-2])) >= 0) HTop--;
		Hull[HTop++] = P[i];
	}
	int LTop = HTop;
	for(int i = n-2;i >= 0;i--)
	{
		while(HTop > LTop && valsign((P[i]-Hull[HTop-2])*(Hull[HTop-1]-Hull[HTop-2])) >= 0) HTop--;
		if(i) Hull[HTop++] = P[i];
	}
	return HTop;
}
