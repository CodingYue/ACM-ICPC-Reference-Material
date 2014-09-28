// We all know this one:
__builtin_popcount(a);

// But it is (a bit) slower than:
int _popcount[1 << 16];
for(int i = 0;i < (1<<16);i++) _popcount[i] = (i&1) + _popcount[i >> 1];
inline int popcount(unsigned int x) { return _popcount[x>>16] + _popcount[x&0xFFFF]; }

// Let's do SSE Magic
// <TODO>: extend it to handle batch xor & blah

#define __aligned__ __attribute__((aligned(16)))

uint8_t POPCOUNT_4bit[16] __aligned__ = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
uint32_t ssse3_popcount3(uint8_t* buffer, int chunks16) { // chunks16 % 4 must be 0
    static char MASK_4bit[16] = {0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf};
    uint32_t result = 0;
    __asm__ volatile ("movdqu (%%eax), %%xmm7" : : "a" (POPCOUNT_4bit));
    __asm__ volatile ("movdqu (%%eax), %%xmm6" : : "a" (MASK_4bit));
    __asm__ volatile ("pxor    %%xmm5, %%xmm5" : : ); // xmm5 -- global accumulator

    for(int i = 0;chunks16 > 0;) {
        // max(POPCOUNT_8bit) = 8, thus byte-wise addition could be done
        // for floor(255/8) = 31 iterations
        int k = 0;
#define MAX (7*4)
        if (chunks16 > MAX) {
            k = MAX;
            chunks16 -= MAX;
        }
        else {
            k = chunks16;
            chunks16 = 0;
        }
#undef MAX
        __asm__ volatile ("pxor %xmm4, %xmm4"); // xmm4 -- local accumulator
        for(int n = 0;n < k;n += 4) {
#define body(index) \
            __asm__ volatile( \
                "movdqa   (%%eax), %%xmm0\n" \
                "movdqa    %%xmm0, %%xmm1\n" \
                "psrlw         $4, %%xmm1\n" \
                "pand      %%xmm6, %%xmm0\n" \
                "pand      %%xmm6, %%xmm1\n" \
                "movdqa    %%xmm7, %%xmm2\n" \
                "movdqa    %%xmm7, %%xmm3\n" \
                "pshufb    %%xmm0, %%xmm2\n" \
                "pshufb    %%xmm1, %%xmm3\n" \
                "paddb     %%xmm2, %%xmm4\n" \
                "paddb     %%xmm3, %%xmm4\n" \
                : : "a" (&buffer[index]));
            body(i); body(i + 1*16); body(i + 2*16); body(i + 3*16); // unroll
#undef body
            i += 4*16;
        }
        // update global accumulator (two 32-bits counters)
        __asm__ volatile (
            "pxor   %xmm0, %xmm0\n"
            "psadbw %xmm0, %xmm4\n"
            "paddd  %xmm4, %xmm5\n"
        );
    }
    // finally add together 32-bits counters stored in global accumulator
    __asm__ volatile (
        "movhlps   %%xmm5, %%xmm0   \n"
        "paddd     %%xmm5, %%xmm0   \n"
        "movd      %%xmm0, %%eax    \n"
        : "=a" (result)
    );
    return result;
}
