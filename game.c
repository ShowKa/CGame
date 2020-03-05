#include "iodefine.h"

void game(void);
void endGame();

void game(void) {
	unsigned long int time;
	initLines();
	initBulette();
	initBlocks();
	for (time = 0; time < 120; time++) {
		char alive, broken;
		int r;
		// stat
		start_TPU8();
		// ---
		// move bulette
		// ---
		moveBulettes();
		broken = breakBlockByBulette();
		if (broken) {
			displayLines();
		}
		// ---
		// move block
		// ---
		moveBlocks();
		broken = breakBlockByBulette();
		if (broken) {
			displayLines();
		}
		// ---
		// generate block
		// ---
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
			return;
		}
		// display result
		displayLines();
		// wait
		wait_TPU8();
	}
	// time over
	endGame();
}

void endGame() {
	char message[] = "GAME OVER !!";
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(&message);
	delay_s(5);
	game();
}