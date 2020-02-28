extern char SHIP;
extern char *all[4];

static int movingTo = 1;

void moveUpShip() {
	int cur, next;
	for (cur = 0; cur < 4; cur++) {
		if (all[cur][0] == SHIP) break;
	}
	next = cur + movingTo;
	all[cur][0] = getEmpty();
	all[next][0] = SHIP;
	movingTo = (next == 0 || next == 3) ? (movingTo * -1) : movingTo;
}

char isShip(char target);
char isShip(char target) {
	return target == SHIP;
}

char existShipAt(int r, int c);
char existShipAt(int r, int c) {
	return isShip(all[r][c]);
}