#include <stdio.h>
#include "bulette.h"
typedef struct Bulette Bulette;

const char BULETTE = 0x7d;
Bulette buletteDummy = {0};
Bulette *bulettes = &buletteDummy;

Bulette *getBulettes() {
	return bulettes;
}

Bulette generateBulette(int r, int c) {
	Bulette *bp = (Bulette *)malloc(sizeof(Bulette));
	Bulette *wp = bulettes;
	(*bp).row = r;
	(*bp).column = c;
	(*bp).symbol = 0x7d;
	(*bp).isDummy = 0;
	(*bp).next = &buletteDummy;
	if (wp->next == NULL) {
		bulettes = bp;
		return *bp;
	}
	while(wp->next) {
		if(wp->next->next == NULL) {
			wp->next = bp;
			break;
		}
		wp = wp->next;
	}
	return *bp;
}

void initBulette() {
	buletteDummy.row = -1;
	buletteDummy.column = -1;
	buletteDummy.symbol = BULETTE;
	buletteDummy.isDummy = 1;
	buletteDummy.next = NULL;
	bulettes = &buletteDummy;
}

void moveBulettes() {
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		(*wp).column += 1;
		wp = wp->next;
	}
	//removeDisappearedBulettes();
}

void removeDisappearedBulettes() {
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		Bulette current = *wp;
		//Bulette next = *current.next;
		if (current.column > 19) {
		}
		wp = current.next;
	}
}