<TeX>求线性无关方程组，本质是个消元，不过按照常用的形式进行了压位（这里是31位）。可以顺便维护出一组基。</TeX>

for(int i = 0;i < n;i++) {
	for(int j = 31;j >= 0;j--) {
		if(xx[i] & (1LL<<j)) {
			if(!ind[j]) { ind[j] = xx[i]; break; }
			else xx[i] ^= ind[j];
		}
	}
}