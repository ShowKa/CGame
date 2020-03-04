#include "iodefine.h"

void game(void);
void game(void) {
	unsigned long int time;
	initLines();
	initBulette();
	initBlocks();
	for (time = 0; time < 120; time++) {
		int r;
		// stat
		start_TPU8();
		// ---
		// move block if exists
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
		// display result
		displayLines();
		// wait
		wait_TPU8();
	}
}

void endGame();
void endGame() {
	char message[] = "GAME OVER !!";
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(&message);
	delay_s(5);
	game();
}