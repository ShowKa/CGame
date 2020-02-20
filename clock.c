#include <stdio.h>

void printClock(char *arr, int number);
int hourOf(int time);
int minuteOf(int time);
int secondOf(int time);
char isAm(int time);

static const char AM[] ="AM";
static const char PM[] ="PM";
static const int SECONDS_IN_A_DAY = 60 * 60 * 24;
static const int START_TIME_OF_NOON = 60 * 60 * 12;
static const int SPAN_OF_A_SECOND = 1000; // milli second

void printClock(char *arr, int number) {
	*arr = number < 10 ? '0' : (number / 10) + '0';
	arr++;
	*arr = (number % 10) + '0';
}

int hourOf(int time) {
	return time / 3600;
}

int minuteOf(int time) {
	int _m = time % 3600;
	return _m / 60;
}

int secondOf(int time) {
	int _m = time % 3600;
	return _m % 60;
}

char isAm(int time) {
	return time < START_TIME_OF_NOON;
	//return 0;
}

void clock(void) {
	int time;
	char display[12];
	char *display_p;
	display[2] = ' ';
	display[5] = ':';
	display[8] = ':';
	display[11] = 0x00;
	for (time = 0; time < SECONDS_IN_A_DAY; time++) {
		// is am?
		char timeIsAm = isAm(time);
		// 12 or 24?
		char displayFor12Hours = slide0IsOn();
		// get clock nums of time
		int h24 = hourOf(time);
		int h12 = timeIsAm ? h24 : h24 - 12;
		int m = minuteOf(time);
		int s = secondOf(time);
		// print am/pm
		display[0] = timeIsAm ? AM[0] : PM[0];
		display[1] = timeIsAm ? AM[1] : PM[1];
		// print time as clock with padding 00
		display_p = display;
		display_p += 3;
		printClock(display_p, displayFor12Hours ? h12 : h24);
		display_p += 3;
		printClock(display_p, m);
		display_p += 3;
		printClock(display_p, s);
		// display on LCD
		LCD_locate_2nd(5);
		LCD_putstr(&display);
		// wait 1 second
		delay_ms(SPAN_OF_A_SECOND);
	}
	// next day
	clock();
}


