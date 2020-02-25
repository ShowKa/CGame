#include "iodefine.h"

void game(void);
void game(void) {
	unsigned long int i, time;
	char _1[21], _2[21], _3[21], _4[21];
	char *all[4] = {_1, _2, _3, _4};
	_1[20] = _2[20] = _3[20] = _4[20] = 0x00;
	for (i =  0; i < 20; i++) {
		_1[i] = 0x20;
		_2[i] = 0x20;
		_3[i] = 0x20;
		_4[i] = 0x20;
	}

	for (time = 0; time < 120; time++) {
		int r;
		// stat
		start_TPU8();
		// ---
		// move block if exists
		// ---
		
		// ---
		// generate block
		// ---
		// which row?
		r = decideRow();
		if (r != -1) {
			all[r][19] = 0xff;
		}
		//----
		// display LCD
		// ---
		LCD_locate_1st(1);
		LCD_putstr(&_1);
		LCD_locate_2nd(1);
		LCD_putstr(&_2);
		LCD_locate_3rd(1);
		LCD_putstr(&_3);
		LCD_locate_4th(1);
		LCD_putstr(&_4);
		// wait
		wait_TPU8();
	}
}
