#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// プロトタイプ
void irq_03();

void irq_03() {
	while(1) {
		setpsw_i();
		delay_ms(500);
	}
}

void countFrom9() {
	int i = 0;
	// 優先度の高い割り込みがあれば、そちらを優先する
	setpsw_i();
	for(i = 0; i < 9; i++) {
		int count = 9 - i;
		turnOnLed(0xaa);
		delay_ms(401);
		turnOnLed(0x55);
		displayMySeg(count);
		delay_ms(402);
	}
	displayMySeg(0);
	turnOffAllLed();
	// force timer working
	start_TIMER();
}

void countFrom3() {
	int i = 0;
	//setpsw_i();
	for(i = 0; i < 3; i++) {
		int count = 3 - i;
		turnOnLed(0xf0);
		delay_ms(403);
		turnOnLed(0x0f);
		displayMySeg(count);
		delay_ms(404);
	}
	displayMySeg(0);
	turnOffAllLed();
	// force timer working
	start_TIMER();
}

