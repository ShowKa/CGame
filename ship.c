#include "ship.h"
#include "bulette.h"
typedef struct Bulette Bulette;
typedef struct Ship Ship;

static Ship theShip = {1, 0, 0x2A};

void moveUpShip() {
	static int movingTo = 1;
	int cur, next;
	cur = theShip.row;
	next = cur + movingTo;
	theShip.row = next;
	movingTo = (next == 0 || next == 3) ? (movingTo * -1) : movingTo;
}

char isShip(char target) {
	return target == theShip.symbol;
}

int getRowOfShip() {
	return theShip.row;
}

int launch() {
	int r = getRowOfShip();
	Bulette generated;
	if (existBuletteAt(r, 1)) {
		return 0;
	}
	generated = generateBulette(r, 1);
	return generated.isDummy ? 1 : 0;
}

char getShipSymbol() {
	return theShip.symbol;
}

Ship getShip() {
	return theShip;
}
