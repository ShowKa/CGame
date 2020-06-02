#include <stdio.h>
#include "bulette.h"
typedef struct Bulette Bulette;

const char BULETTE = 0x7d;
Bulette buletteDummy = {0};
Bulette *bulettes;

Bulette *getBulettes() {
	return bulettes;
}

Bulette generateBulette(int r, int c) {
	Bulette *bp = (Bulette *)malloc(sizeof(Bulette));
	(*bp).row = r;
	(*bp).column = c;
	(*bp).symbol = 0x7d;
	(*bp).isDummy = 0;
	(*bp).next = bulettes;
	bulettes = bp;
	return *bp;
}

void initBulette() {
	Bulette *wp = bulettes;
	while (!wp->isDummy) {
		Bulette *backup_p = wp->next;
		free(wp);
		wp = backup_p;
	}
	buletteDummy.row = -1;
	buletteDummy.column = -1;
	buletteDummy.symbol = BULETTE;
	buletteDummy.isDummy = 1;
	buletteDummy.next = &buletteDummy;
	bulettes = &buletteDummy;
}

void moveBulettes() {
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		(*wp).column += 1;
		wp = wp->next;
	}
	removeDisappearedBulettes();
}

void removeFirstBulette() {
	Bulette first = *bulettes;
	bulettes = first.next;
	free(&first);
}

void removeBulettesByIndex(int index) {
	int i = 0;
	Bulette *target_p = bulettes;
	Bulette *prev_p = NULL;
	if (index < 0) {
		return;
	}
	if (index == 0) {
		removeFirstBulette();
		return;
	}
	while(i < index) {
		prev_p = target_p;
		target_p = target_p->next;
		i++;
	}
	prev_p->next = target_p->next;
	free(target_p);
}

void removeDisappearedBulettes() {
	int i = 0;
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		if (wp->column > 19) {
			wp = wp->next;
			removeBulettesByIndex(i);
			continue;
		}
		wp = wp->next;
		i++;
	}
}

void breakBulettes(Bulette *bulette) {
	bulette->column = 20;
	removeDisappearedBulettes();
}

char existBuletteAt(int r, int c) {
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		if ((*wp).row == r && (*wp).column == c) {
			return 0x01;
		}
		wp = wp->next;
	}
	return 0x00;
}