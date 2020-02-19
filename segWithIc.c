#include	"iodefine.h"

// port9 SEG7
#define   SEG01_IO  PORT9.PDR.BYTE
#define   SEG01   PORT9.PODR.BYTE

void initSegWithIc(void);
void initSegWithIc(void) {
	SEG01_IO = 0xff;
}

void displaySegWithIc(char number) {
	SEG01 = number;
}