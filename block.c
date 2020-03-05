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
		// ���v�f���f�B�X�v���C�\���̈�̊O�ɏo���ꍇ�A���Y�v�f�폜
		if (current_p->column < 0) {
			// �܂����X�g�擪�ɂ���ꍇ�A���̗v�f�����X�g�̐擪�ɂ���
			if (current_p == prev_p) {
				blocks = next_p;
			// ���X�g�擪�ł͂Ȃ��ꍇ�A�O�Ǝ���A������B
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