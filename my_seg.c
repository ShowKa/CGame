#include	"iodefine.h"

// portD ©ìŠî”Õ‚Ì7seg
#define   SEG02_IO PORTD.PDR.BYTE
#define   SEG02 PORTD.PODR.BYTE

void initMySEG();
void displayMySeg(int number);
int seg7_ic(int number);
int seg7_ic_reverse(char seg);

static char seg_dec_arr[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
	0x6d, 0x7c, 0x07,0x7f, 0x67};
static char seg_dec_err = 0xF9;

void initMySEG() {
	SEG02_IO = 0xff;
}

void displayMySeg(int number) {
	SEG02 = seg7_ic(number);
}

int seg7_ic(int number) {
	if (number >=0 && number <=9) {
		return seg_dec_arr[number];
	} else {
		return seg_dec_err;
	}
}

int seg7_ic_reverse(char seg) {
	int i, size = sizeof(seg_dec_arr);
	for (i = 0; i < size; i++) {
		if (seg == seg_dec_arr[i]) {
			return i;
		}
	}
	return -1;
}