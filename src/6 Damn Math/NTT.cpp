<TeX> 最终结果 mod $P$.

$E_i \equiv g^{(P_i-1) \div N_1} \pmod{P_i}$ $F_i \equiv 1 \div E_i \pmod{P_i} $ $I_i \equiv 1 \div N_1 \pmod{P_i}$ </TeX>
namespace NTT {
	const int P = MOD;
	const int P1 = 998244353;
	const int P2 = 995622913;
	const int g1 = 3;
	const int g2 = 5;
	const LL M1 = 397550359381069386LL;
	const LL M2 = 596324591238590904LL;
	const LL MM = 993874950619660289LL;
	int I1, I2;

	int N;
	int a[MaxN], b[MaxN], c[MaxN];
	LL mul(LL x, LL y, LL z) {
		return (x * y - (LL) (x / (long double) z * y + 1e-3) * z + z) % z;
	}
	int crt(int x1, int x2) {
		return (mul(M1, x1, MM) + mul(M2, x2, MM)) % MM % P;
	}
	void NTT(int *A, int pm, int g) {
		if (g < 0) g = fpow(-g, pm - 2, pm);
		int pw = fpow(g, (pm - 1) / N, pm);
		for (int m = N, h; h = m / 2, m >= 2; pw = (LL) pw * pw % pm, m = h) {
			for (int i = 0, w = 1; i < h; ++i, w = (LL) w * pw % pm)
			for (int j = i; j < N; j += m) {
				int k = j + h, x = (A[j] - A[k] + pm) % pm;
				A[j] += A[k]; A[j] %= pm;
				A[k] = (LL) w * x % pm;
			}
		}
		for (int i = 0, j = 1; j < N - 1; ++j) {
			for (int k = N / 2; k > (i^=k); k /= 2);
			if (j < i) swap(A[i], A[j]);
		}
	}
	void solve(int *A, int *B, int *C, int n) {

		N = 1;
		while (N < (n << 1)) N <<= 1;
		memset(C, 0, sizeof (*C)*N);
		for (int i = n; i < N; ++i) A[i] = B[i] = 0;
		memcpy(a, A, sizeof (*A)*N);
		memcpy(b, B, sizeof (*B)*N);

		NTT(a, P1, g1);
		NTT(b, P1, g1);
		for (int i = 0; i < N; ++i) c[i] = (LL) a[i] * b[i] % P1;
		NTT(c, P1, -g1);

		NTT(A, P2, g2);
		NTT(B, P2, g2);
		for (int i = 0; i < N; ++i) C[i] = (LL) A[i] * B[i] % P2;
		NTT(C, P2, -g2);

		I1 = fpow(N, P1 - 2, P1);
		I2 = fpow(N, P2 - 2, P2);
		for (int i = 0; i < n; ++i) {
			C[i] = crt((LL) c[i] * I1 % P1, (LL) C[i] * I2 % P2);
		}
	}
}

