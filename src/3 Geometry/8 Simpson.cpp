inline double simpson(double fl,double fr,double fmid,double l,double r) { return (fl+fr+4.0*fmid)*(r-l)/6.0; }
double rsimpson(double slr,double fl,double fr,double fmid,double l,double r)
{
	double mid = (l+r)*0.5;
	double fml = f((l+mid)*0.5);
	double fmr = f((mid+r)*0.5);
	double slm = simpson(fl,fmid,fml,l,mid);
	double smr = simpson(fmid,fr,fmr,mid,r);
	if(fabs(slr-slm-smr) < eps) return slm+smr;
	return rsimpson(slm,fl,fmid,fml,l,mid)+rsimpson(smr,fmid,fr,fmr,mid,r);
}
