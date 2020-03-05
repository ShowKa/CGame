#include <stdio.h>
#include "block.h"
typedef struct Block Block;

const char BLOCK = 0xff;
Block *blocks;
Block blockDummy= {0};

void initBlocks() {
	blockDummy.row = -1;
	blockDummy.column = -1;
	blockDummy.symbol = BLOCK;
	blockDummy.velocity = 0;
	blockDummy.next = NULL;
	blockDummy.isDummy= 1;
	blocks = &blockDummy;
}

Block generateBlock(int row) {
	Block *new_bp = (Block *)malloc(sizeof(Block));
	Block *wp = blocks;
	(*new_bp).row = row;
	(*new_bp).column = 19;
	(*new_bp).symbol = 0xff;
	(*new_bp).next = &blockDummy;
	(*new_bp).isDummy = 0;
	if (wp->next == NULL) {
		blocks = new_bp;
		return *new_bp;
	}
	while(wp->next) {
		if(wp->next->next == NULL) {
			wp->next = new_bp;
			break;
		}
		wp = wp->next;
	}
	return *new_bp;
}

int decideRow() {
	int a = random(12);
	if (a >= 4) {
		a = -1;
	}
	return a;
}

char isBlock(char target) {
	return target == BLOCK;
}

void moveBlocks() {
	Block *wp = blocks;
	while (wp->next != NULL) {
		(*wp).column -= 1;
		wp = wp->next;
	}
	removeDisappearedBlocks();
}

Block *getBlocks() {
	return blocks;
}

void removeDisappearedBlocks() {
	Block *wp = blocks;
	Block *prev_p = blocks;
	while (!wp->isDummy) {
		char removed = 0;
		Block *current_p = wp;
		Block *next_p = wp->next;
		// 現要素がディスプレイ表示領域の外に出た場合、当該要素削除
		if (current_p->column < 0) {
			// まだリスト先頭にいる場合、次の要素をリストの先頭にする
			if (current_p == prev_p) {
				blocks = next_p;
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

void breakBlock(int row, int column) {
	Block *wp = blocks;
	while (wp->next != NULL) {
		if (wp->row == row && wp->column == column) {
			(*wp).column = -1;
			break;
		}
		wp = wp->next;
	}
	removeDisappearedBlocks();
}