int MinimumRepresentation(char *s, int n)
{
	int i = 0, j = 1, k = 0, t;
	while(i < n && j < n && k < n) {
		t = s[(i + k) % n] - s[(j + k) % n];
		if(!t) k++;
		else{
			if(t > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) ++ j;
			k = 0;
		}
	}
	return (i < j ? i : j);
}
