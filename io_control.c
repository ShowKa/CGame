#include	"iodefine.h"

// portA LED
#define  LED_IO PORTA.PDR.BYTE
#define  LED PORTA.PODR.BYTE

// portC controll switch
#define  CON_SW_IO PORTC.PDR.BYTE
#define  CON_SW PORTC.PIDR.BYTE
#define  CON_SW_DONE PORTC.PIDR.BIT.B0

void initPDR(void)
{
	initSegWithIc();
	initMySEG();
	initLed();
	sw_init();
}