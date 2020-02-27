#include "iodefine.h"

void game(void);
void game(void) {
	unsigned long int time;
	initLines();
	for (time = 0; time < 120; time++) {
		int r;
		// stat
		start_TPU8();
		// ---
		// move block if exists
		// ---
		moveBlock();
		// ---
		// add block
		// ---
		// which row?
		r = decideRow();
		if (r != -1) {
			addBlock(r);
		}
		// display result
		displayLines();
		// wait
		wait_TPU8();
	}
}
