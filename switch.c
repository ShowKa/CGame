#include	"iodefine.h"

// portB switch
#define   SW_IO PORTB.PDR.BYTE		
#define   SW PORTB.PIDR.BYTE			//ポートB入力データ SW（DIP,PUSH)
#define   SW_0 PORTB.PIDR.BIT.B0		//ポートBスイッチ
#define   SW_1 PORTB.PIDR.BIT.B1		//ポートBスイッチ
#define   SW_2 PORTB.PIDR.BIT.B2		//ポートBスイッチ
#define   SW_3 PORTB.PIDR.BIT.B3		//ポートBスイッチ
#define   SW_YEL PORTB.PIDR.BIT.B4		//ポートB7 黄ボタンスイッチ
#define   SW_GRN PORTB.PIDR.BIT.B5		//ポートB7 緑ボタンスイッチ
#define   SW_ORG PORTB.PIDR.BIT.B6		//ポートB7 橙ボタンスイッチ
#define   SW_RED PORTB.PIDR.BIT.B7		//ポートB7 赤ボタンスイッチ

void sw_init();
char getPushSwitchState();
char getSlideSwitchState();
char slide0IsOn(void);

void sw_init() {
	SW_IO = 0x00;
}

char getPushSwitchState() {
	return SW >> 4;
}

char getSlideSwitchState() {
	return SW & 0x0f;
}

char slide0IsOn(void) {
	if (SW_0 == 1) {
		return 0x01;
	} else {
		return 0x00;
	}
}

char slide1IsOn() {
	return SW_1 == 1;
}

char slide2IsOn() {
	return SW_2 == 1;
}

char slide3IsOn() {
	return SW_3 == 1;
}
