<TeX>修改 esp 到手动分配的内存。
慎用！可能违反某些规则或造成不必要的 RE/WA 。</TeX>
int main(void)
{
	char* SysStack = NULL;
	char* MyStack = new char[33554432];
	MyStack += 33554432-1048576; // 32M
	__asm__(
		"movl %%esp,%%eax\n\t"
		"movl %1,%%esp\n\t"
		:"=a"(SysStack)
		:"m"(MyStack)
	);
	mmain();
	__asm__(
		"movl %0,%%esp\n\t"
		::"m"(SysStack)
	);
	return 0;
}
