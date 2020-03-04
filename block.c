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
	while (!wp->isDummy) {
		Block current_b = *wp;
		// remove
		if (current_b.column < 0) {
			blocks = current_b.next;
			wp = current_b.next;
			free(&current_b);
		} else {
			break;
		}
	}
}