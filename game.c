#include "iodefine.h"
#include "vect.h"

void game(void);
void endGame();
void checkBrokenBlock();

void game(void) {
	unsigned long int time;
	initLines();
	initBulette();
	initBlocks();
	initScore();
	for (time = 0; time < 120; time++) {
		char alive;
		int r;
		// stat
		start_TPU8();
		// ---
		// move bulette
		// ---
		moveBulettes();
		checkBrokenBlock();
		// ---
		// move block
		// ---
		moveBlocks();
		checkBrokenBlock();
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
	int p_scoreMessage = getScoreMessage();
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(&message);
	LCD_locate(1,3);
	LCD_putstr(p_scoreMessage);
	delay_s(5);
	game();
}

// ICU IRQ0
void Excep_ICU_IRQ0(void){
	char timeIsStart = isStart_TIMER();
	launch();
	displayLines();
	checkBrokenBlock();
	if (timeIsStart) {
		start_TIMER();
	}
}

// ICU IRQ1
void Excep_ICU_IRQ1(void){
	char timeIsStart = isStart_TIMER();
	moveUpShip();
	displayLines();
	if (timeIsStart) {
		start_TIMER();
	}
}

void checkBrokenBlock() {
	char broken = breakBlockByBulette();
	if (broken) {
		displayLines();
	}
}
