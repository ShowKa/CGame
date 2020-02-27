// global
char _0[21], _1[21], _2[21], _3[21];
char *all[4] = {_0, _1, _2, _3};

void initLines();
void initLines() {
	unsigned long int i;
	_0[20] = _1[20] = _2[20] = _3[20] = 0x00;
	for (i =  0; i < 20; i++) {
		_0[i] = 0x20;
		_1[i] = 0x20;
		_2[i] = 0x20;
		_3[i] = 0x20;
	}
}

void displayLines();
void displayLines() {
	int i;
	for (i = 0; i < 4; i++) {
		LCD_locate(1, i+1);//caution
		LCD_putstr(all[i]);
	}
}
