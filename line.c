#include <stdio.h>
#include "bulette.h"
#include "ship.h"
#include "block.h"

typedef struct Bulette Bulette;
typedef struct Ship Ship;
typedef struct Block Block;

// global
char _0[21], _1[21], _2[21], _3[21];
char *all[4] = {_0, _1, _2, _3};

char EMPTY = 0x20;

void setBulettesIntoLine();
void displayLines();
char getEmpty();
void initLines();

void initLines() {
	int i;
	_0[20] = _1[20] = _2[20] = _3[20] = 0x00;
	for (i =  0; i < 20; i++) {
		_0[i] = EMPTY;
		_1[i] = EMPTY;
		_2[i] = EMPTY;
		_3[i] = EMPTY;
	}
}

void displayLines() {
	int i;
	Ship ship;
	Block *blocks;
	Bulette *bulettes;
	// init
	initLines();
	// block
	blocks = getBlocks();
	while (blocks->next != NULL) {
		Block b = *blocks;
		all[b.row][b.column] = b.symbol;
		blocks = blocks->next;
	}
	// bulette
	bulettes = getBulettes();
	while (!bulettes->isDummy) {
		Bulette bul = *bulettes;
		all[bul.row][bul.column] = bul.symbol;
		bulettes = bul.next;
	}
	// ship
	ship = getShip();
	all[ship.row][ship.column] = ship.symbol;
	// display
	for (i = 0; i < 4; i++) {
		LCD_locate(1, i+1);//watch out
		LCD_putstr(all[i]);
	}
}

char getEmpty() {
	return EMPTY;
}

char isShipAlive() {
	Ship ship;
	Block *blocks;
	Block b;
	// ship
	ship = getShip();
	// block
	blocks = getBlocks();
	b = *blocks;
	while (!b.isDummy) {
		// dead
		if (ship.row == b.row && ship.column == b.column) {
			return 0;
		}
		b = *b.next;
	}
	return 1;
}
