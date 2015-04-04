register char *_sp __asm__("rsp"); // esp / sp
int main(void) {
	const int size = 64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys = _sp; _sp = mine; mmain(); _sp = sys;
	return 0;
}