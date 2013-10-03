<TeX>$n$需要为2的次幂，sign传入1时正变换，-1时逆变换，逆变换后需要手动除以$n$。</TeX>
typedef complex<double> cplx;
inline unsigned int intrev(unsigned x)
{
	x = ((x & 0x55555555U) << 1) | ((x & 0xAAAAAAAAU) >> 1);
	x = ((x & 0x33333333U) << 2) | ((x & 0xCCCCCCCCU) >> 2);
	x = ((x & 0x0F0F0F0FU) << 4) | ((x & 0xF0F0F0F0U) >> 4);
	x = ((x & 0x00FF00FFU) << 8) | ((x & 0xFF00FF00U) >> 8);
	x = ((x & 0x0000FFFFFU) << 16) | ((x & 0xFFFF0000U) >> 16);
	return x;
};
void fft(int sign, cplx* data, int n)
{
	int d = 1+__builtin_clz(n);
	double theta = sign * 2.0 * PI / n;
	for(int m = n;m >= 2;m >>= 1, theta *= 2)
	{
		cplx tri = cplx(cos(theta),sin(theta));
		cplx w = cplx(1,0);
		for(int i = 0, mh = m >> 1; i < mh; i++)
		{
			for(int j = i;j < n;j += m)
			{
				int k = j+mh;
				cplx tmp = data[j]-data[k];
				
				data[j] += data[k];
				data[k] = w * tmp;
			}
			w *= tri;
		}
	}
	for(int i = 0;i < n;i++)
	{
		int j = intrev(i) >> d;
		if(j < i) swap(data[i],data[j]);
	}
	return;
}