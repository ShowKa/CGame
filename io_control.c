#include	"iodefine.h"

void initPDR(void)
{
	initSegWithIc();
	initMySEG();
	initLed();
	sw_init();
}