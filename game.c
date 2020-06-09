#include "iodefine.h"
#include "vect.h"
#include "Block.h"

void game(void);
void endGame();
void error();
void checkBrokenBlock();

typedef struct Block Block;

void game(void) {
	unsigned long int time;
	initLines();
	initBulette();
	initBlocks();
	initScore();
	initExplosion();
	for (time = 0; time < 120; time++) {
		char alive;
		int r;
		Block generated;
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
			generated = generateBlock(r);
			if (generated.isDummy) {
				char message[16] = "error gen Block";
				message[15] = 0x00;
				error(message);
				return;
			}
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
	// game over message
	char static message[13] = "GAME OVER !!";
	message[12] = 0x00;
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(message);
	// score
	LCD_locate(1,3);
	LCD_putstr(getScoreMessage());
	delay_s(5);
	game();
}

void error(char *message) {
	LCD_clear();
	LCD_locate(1,2);
	LCD_putstr(message);
	delay_s(5);
	game();
}

// ICU IRQ0
void Excep_ICU_IRQ0(void){
	char timeIsStart = isStart_TIMER();
	int errorCode = launch();
	if (errorCode) {
		char message[15] = "cannot launch!";
		message[14] = 0x00;
		error(message);
		return;
	}
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


// CMT0 Š„ž‚Ýˆ—
void Excep_CMT0_CMI0(void){ 
	char timeIsStart = isStart_TIMER();
	twinkleAllExplosion();
	removeDisappearedExplosions();
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
