#include "iodefine.h"

void game(void);
void endGame();

void game(void) {
	unsigned long int time;
	initLines();
	initBulette();
	initBlocks();
	for (time = 0; time < 120; time++) {
		char alive;
		int r;
		// stat
		start_TPU8();
		// ---
		// move block
		// ---
		moveBlocks();
		// ---
		// add block
		// ---
		// which row?
		r = decideRow();
		if (r != -1) {
			generateBlock(r);
		}
		// ---
		// check alive
		// ---
		alive = isShipAlive();
		if (!alive) {
			endGame();
		}
		// display result
		displayLines();
		// wait
		wait_TPU8();
	}
}

void endGame() {
	char message[] = "GAME OVER !!";
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(&message);
	delay_s(5);
	game();
}