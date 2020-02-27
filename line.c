// global
char _0[21], _1[21], _2[21], _3[21];
char *all[4] = {_0, _1, _2, _3};

char BLOCK = 0xff;
char EMPTY = 0x20;
char SHIP = 0x2A;

void initLines();
void initLines() {
	unsigned long int i;
	_0[20] = _1[20] = _2[20] = _3[20] = 0x00;
	for (i =  0; i < 20; i++) {
		_0[i] = EMPTY;
		_1[i] = EMPTY;
		_2[i] = EMPTY;
		_3[i] = EMPTY;
	}
	_1[0] = SHIP;
}

void displayLines();
void displayLines() {
	int i;
	for (i = 0; i < 4; i++) {
		LCD_locate(1, i+1);//caution
		LCD_putstr(all[i]);
	}
}

char getEmpty();
char getEmpty() {
	return EMPTY;
}