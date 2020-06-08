#include <stdio.h>
#include "bulette.h"
#include "ship.h"
#include "block.h"
#include "explosion.h"
#include "score.h"

typedef struct Bulette Bulette;
typedef struct Ship Ship;
typedef struct Block Block;
typedef struct Explosion Explosion;

// global
static char _0[21], _1[21], _2[21], _3[21];
static char *all[4] = {_0, _1, _2, _3};

static const char EMPTY = 0x20;

void displayLines();
void initLines();
char isShipAlive();
char breakBlockByBulette();

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
	Explosion *explosions;
	// init
	initLines();
	// block
	blocks = getBlocks();
	while (!blocks->isDummy) {
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
	// explosion
	explosions = getExplosions();
	while (!explosions->isDummy) {
		Explosion e = *explosions;
		all[e.row][e.column] = e.show ? e.symbol : EMPTY;
		explosions = explosions->next;
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

char breakBlockByBulette() {
	char broken = 0;
	Bulette *bulettes = getBulettes();
	Block *blocks = getBlocks();
	while (!bulettes->isDummy) {
		Bulette *next_bulettes = bulettes->next;
		while (!blocks->isDummy) {
			char sameRow = (blocks->row == bulettes->row);
			char sameColumn = (blocks->column == bulettes->column);
			// 衝突したのでブロックと弾を除去
			if (sameRow && sameColumn) {
				// 爆発
				generateExplosion(blocks->row, blocks->column);
				// ブロック&弾丸破壊
				breakBlock(blocks);
				breakBulettes(bulettes);
				broken = 1;
				// スコア加算
				addPoint(5);
				break;
			}
			blocks = blocks->next;
		}
		blocks = getBlocks();
		bulettes = next_bulettes;
	}
	return broken;
}
