int getcircle(POINT& a,POINT& b,POINT& c,POINT& O,double& r)
{
	double a1 = 2.0*(a.x-b.x);
	double b1 = 2.0*(a.y-b.y);
	double c1 = a.x*a.x-b.x*b.x + a.y*a.y-b.y*b.y;
	double a2 = 2.0*(a.x-c.x);
	double b2 = 2.0*(a.y-c.y);
	double c2 = a.x*a.x-c.x*c.x + a.y*a.y-c.y*c.y;
	O.x = (c1*b2-c2*b1)/(a1*b2-a2*b1);
	O.y = (c1*a2-c2*a1)/(b1*a2-b2*a1);
	r = eudis(a,O);
	return 0;
}

POINT pt[100010] = {0};

int main(void)
{
	int n = 0;
	scanf("%d",&n);
	for(int i = 0;i < n;i++) scanf("%lf %lf",&pt[i].x,&pt[i].y);
	random_shuffle(pt,pt+n);
	
	double r = 0.0;
	POINT O = pt[0];
	for(int i = 1;i < n;i++)
	{
		if(eudis(pt[i],O)-r > -eps)
		{
			O.x = (pt[0].x+pt[i].x)/2.0;
			O.y = (pt[0].y+pt[i].y)/2.0;
			r = eudis(O,pt[0]);
			for(int j = 0;j < i;j++)
			{
				if(eudis(pt[j],O)-r > -eps)
				{
					O.x = (pt[i].x+pt[j].x)/2.0;
					O.y = (pt[i].y+pt[j].y)/2.0;
					r = eudis(O,pt[i]);
					for(int k = 0;k < j;k++)
					{
						if(eudis(pt[k],O)-r > -eps)
						{
							getcircle(pt[i],pt[j],pt[k],O,r);
						}
					}
				}
			}
		}
	}
	printf("%.10f\n%.10f %.10f\n",r,O.x,O.y);
	while(getchar() != EOF);
	return 0;
}