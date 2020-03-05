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
	removeDisappearedBulettes();
}

void removeDisappearedBulettes() {
	Bulette *wp = bulettes;
	Bulette *prev_p = bulettes;
	while(!wp->isDummy) {
		char removed = 0;
		Bulette *current_p = wp;
		Bulette *next_p = current_p->next;
		// 現要素がディスプレイ表示領域の外に出た場合、当該要素削除
		if (current_p->column > 19) {
			// まだリスト先頭にいる場合、次の要素をリストの先頭にする
			if (current_p == prev_p) {
				bulettes = next_p;
			// リスト先頭ではない場合、前と次を連結する。
			} else {
				prev_p->next = current_p->next;
			}
			removed = 1;
		}
		// increment
		wp = current_p->next;
		// free memory
		if (removed) {
			// prev_p = prev_p;
			free(current_p);
		} else {
			prev_p = current_p;
		}
	}
}

void breakBulettes(int row, int column) {
	Bulette *wp = bulettes;
	while(!wp->isDummy) {
		if (wp->row == row && wp->column == column) {
			(*wp).column = 20;
			break;
		}
		wp = wp->next;
	}
	removeDisappearedBulettes();
}