<TeX> 最终结果 mod $P$. $N \leq 200000$ 

$E_i \equiv g^{(P_i-1) \div N_1} \pmod{P_i}$ $F_i \equiv 1 \div E_i \pmod{P_i} $ $I_i \equiv 1 \div N_1 \pmod{P_i}$ </TeX>
namespace NTT {
	const int P = 1000003; const int N = 100010; const int N1 = 262144;
	const int P1 = 998244353; const int P2 = 995622913;
	const int E1 = 996173970; const int E2 = 88560779;
	const int F1 = 121392023; const int F2 = 840835547;
	const int I1 = 998240545; const int I2 = 995619115;
	const LL M1 = 397550359381069386LL; const LL M2 = 596324591238590904LL;
	const LL MM = 993874950619660289LL;
	LL mul(LL x, LL y, LL z) {
		return (x * y - (LL) (x / (long double) z * y + 1e-3) * z + z) % z;
	}
	int crt(int x1, int x2) {
		return (mul(M1, x1, MM) + mul(M2, x2, MM)) % MM % P;
	}
	void NTT(int *A, int PM, int PW) {
		for (int m = N1, h; h = m / 2, m >= 2; PW = (LL) PW * PW % PM, m = h) {
			for (int i = 0, w = 1; i < h; ++i, w = (LL) w * PW % PM)
			for (int j = i; j < N1; j += m) {
				int k = j + h, x = (A[j] - A[k] + PM) % PM;
				A[j] += A[k]; A[j] %= PM;
				A[k] = (LL) w * x % PM;
			}
		}
		for (int i = 0, j = 1; j < N1 - 1; ++j) {
			for (int k = N1 / 2; k > (i^=k); k /= 2);
			if (j < i) swap(A[i], A[j]);
		}
	}
	int A1[MaxN], B1[MaxN], C1[MaxN];
	void mul(int *A, int *B, int *C, int n) {
		memset(C, 0, sizeof(*C)*N1);
		memcpy(A1, A, sizeof(*A)*N1);
		memcpy(B1, B, sizeof(*B)*N1);
		NTT(A1, P1, E1);
		NTT(B1, P1, E1);
		for (int i = 0; i < N1; ++i) C1[i] = (LL) A1[i] * B1[i] % P1;
		NTT(C1, P1, F1);
		for (int i = 0; i < N1; ++i) C1[i] = (LL) C1[i] * I1 % P1;
		NTT(A, P2, E2);
		NTT(B, P2, E2);
		for (int i = 0; i < N1; ++i) C[i] = (LL) A[i] * B[i] % P2;
		NTT(C, P2, F2);
		for (int i = 0; i < N1; ++i) C[i] = (LL) C[i] * I2 % P2;
		for (int i = 0; i < N1; ++i) C[i] = crt(C1[i], C[i]);
		for (int i = n; i < N1; ++i) C[i] = 0;
	}
}
