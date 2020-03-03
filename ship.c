#include "ship.h"
#include "bulette.h"
typedef struct bulette bulette;
typedef struct ship ship;

extern char *all[4];

static const ship theShip = {1, 0x2A};

void moveUpShip() {
	static int movingTo = 1;
	int cur, next;
	for (cur = 0; cur < 4; cur++) {
		if (all[cur][0] == theShip.symbol) break;
	}
	next = cur + movingTo;
	all[cur][0] = getEmpty();
	all[next][0] = theShip.symbol;
	movingTo = (next == 0 || next == 3) ? (movingTo * -1) : movingTo;
}

char isShip(char target) {
	return target == theShip.symbol;
}

char existShipAt(int r, int c) {
	return isShip(all[r][c]);
}

int getRowOfShip() {
	int i;
	for (i = 0; i < 4; i++) {
		if ( existShipAt(i, 0) ) break;
	}
	return i;
}

void launch() {
	int r = getRowOfShip();
	bulette b = generateBulette(r, 1);
}

char getShipSymbol() {
	return theShip.symbol;
}