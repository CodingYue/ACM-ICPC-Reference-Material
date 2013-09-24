<TeX>如果怀疑被畸形数据了并且时间很多，试试 $$\int_{a}^{b} f(x) \, dx \approx \frac{(b-a)}{8}\left[f(a) + 3f\left(\frac{2a+b}{3}\right) + 3f\left(\frac{a+2b}{3}\right) + f(b)\right]\, $$ </TeX>
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
