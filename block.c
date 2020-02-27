extern char *all[4];

int decideRow(void);
int decideRow(void) {
	int a = random(12);
	if (a >= 4) {
		a = -1;
	}
	return a;
}

void addBlock(int row) {
	all[row][19] = 0xff;
}