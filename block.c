int decideRow(void);
int decideRow(void) {
	int a = (rand() % 12);
	if (a >= 5) {
		a = 0;
	}
	return a;
}