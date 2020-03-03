#include <stdio.h>
#include "bulette.h"

typedef struct bulette bulette;

bulette buletteDummy = {-1, -1, 0x7d, NULL};
bulette *bulettes = &buletteDummy;

bulette generateBulette(int r, int c) {
	bulette *bp = (bulette *)malloc(sizeof(bulette));
	bulette *wp = bulettes;
	(*bp).row = r;
	(*bp).column = c;
	(*bp).symbol = 0x7d;
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
	bulettes = &buletteDummy;
}