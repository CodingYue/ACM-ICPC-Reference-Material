<TeX> 二维凸包 solve to b[]. </TeX>
void graham() {
	
	sort(b, b + n);
	Point t = b[0];
	for (int i = 0; i < n; ++i) b[i] = b[i] - t;
	int m = unique(b, b + n) - b;
	//printf("%d\n", cmp(b[0], b[1]));
	
	//printf("%.10lf\n%.10lf\n", atan2(0, 0), atan2(0.70, -0.40));
	sort(b + 1, b + m, cmp);

	top = 2;
	stack[1] = 0;
	stack[2] = 1;
	for (int i = 2; i < m; ++i) {
		while (top > 1 && dcmp0(xcross2D(b[stack[top - 1]], b[stack[top]], b[i])) <= 0 ) --top;
		stack[++top] = i;
	}
}