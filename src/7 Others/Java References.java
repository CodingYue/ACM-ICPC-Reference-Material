// DecimalFormat if you want to output double with specific precision
// FileInputStream if file is needed. FileReader, FileWriter?
// new PrintWrite(new BufferedWriter(  ...

BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
StringTokenizer tokenizer = null;

public String next() {
	while (tokenizer == null || !tokenizer.hasMoreTokens()) {
		try {
			tokenizer = new StringTokenizer(reader.readLine());
		} catch(IOException e) {
			throw new RuntimeException(e);
		}
	}
	return tokenizer.nextToken();
}

public int nextInt() {
	return Integer.parseInt(next()); // Double.parseDouble .....
}