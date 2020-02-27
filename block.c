extern char *all[4];

extern char BLOCK;

int decideRow(void);
int decideRow(void) {
	int a = random(12);
	if (a >= 4) {
		a = -1;
	}
	return a;
}

void addBlock(int row) {
	all[row][19] = BLOCK;
}

char isBlock(char target);
char isBlock(char target) {
	return target == BLOCK;
}

void moveBlock() {
	int r, c;
	for (r = 0; r < 4; r++) {
		char *row = all[r];
		for (c = 0; c < 20; c++) {
			char target = row[c];
			if (isBlock(target)) {
				// move left
				if (c > 0) {
					all[r][c-1] = BLOCK;
				}
				// del if exists
				all[r][c] = getEmpty();
			}
		}
	}
}