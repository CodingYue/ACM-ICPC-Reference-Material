<TeX>
	整数划分。
	五边形数 $\frac{3j^{2}-j}{2}$
	
	Generate function $\prod\limits_{n=1}^{\infty} 1+x^n+x^{2n}+x^{3n}+\dots = \prod\limits_{n=1}^{\infty} \frac{1}{1-x^{n}} $

	$ \prod\limits_{n=1}^\infty (1-x^n)=\sum\limits_{k=-\infty}^\infty(-1)^kx^{k(3k-1)/2}=\sum\limits_{k=0}^\infty(-1)^kx^{k(3k\pm 1)/2} $ 
</TeX>

void parition(int n) {
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, r = 1; i - (3*j*j-j) / 2 >= 0; ++j, r *= -1) {
            dp[i] = (dp[i] + dp[i - (3*j*j-j) / 2] * r) % MOD;
            if (i - (3*j*j + j) / 2 >= 0)
                dp[i] = (dp[i] + dp[i - (3*j*j+j) / 2] * r) % MOD;
        }
    }
}

