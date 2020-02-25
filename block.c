int decideRow(void);
int decideRow(void) {
	int a = random(12);
	if (a >= 4) {
		a = -1;
	}
	return a;
}