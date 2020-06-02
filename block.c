#include <stdio.h>
#include "block.h"
typedef struct Block Block;

static const char BLOCK = 0xff;
static Block *blocks;
static Block blockDummy= {0};

void initBlocks() {
	Block *wp = blocks;
	while (!wp->isDummy) {
		Block *backup_p = wp->next;
		free(wp);
		wp = backup_p;
	}
	blockDummy.row = -1;
	blockDummy.column = -1;
	blockDummy.symbol = BLOCK;
	blockDummy.velocity = 0;
	blockDummy.next = &blockDummy;
	blockDummy.isDummy= 1;
	blocks = &blockDummy;
}

Block generateBlock(int row) {
	Block *new_bp = (Block *)malloc(sizeof(Block));
	(*new_bp).row = row;
	(*new_bp).column = 19;
	(*new_bp).symbol = 0xff;
	(*new_bp).velocity = 1;
	(*new_bp).next = blocks;
	(*new_bp).isDummy = 0;
	blocks = new_bp;
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
	while (!wp->isDummy) {
		(*wp).column -= 1;
		// ƒXƒRƒAŒ¸
		if ((*wp).column == -1) {
			addPoint(-10);
		}
		wp = wp->next;
	}
	removeDisappearedBlocks();
}

Block *getBlocks() {
	return blocks;
}

void removeFirstBlock() {
	Block first = *blocks;
	blocks = first.next;
	free(&first);
}

void removeBlockByIndex(int index) {
	int i = 0;
	Block *target_p = blocks;
	Block *prev_p = NULL;
	if (index < 0) {
		return;
	}
	if (index == 0) {
		removeFirstBlock();
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

void removeDisappearedBlocks() {
	Block *wp = blocks;
	int i = 0;
	while (!wp->isDummy) {
		if (wp->column < 0) {
			wp = wp->next;
			removeBlockByIndex(i);
			continue;
			
		}
		wp = wp->next;
		i++;
	}
}

void breakBlock(Block *block) {
	block->column = -1;
	removeDisappearedBlocks();
}