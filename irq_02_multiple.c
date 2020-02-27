#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// プロトタイプ
void irq_02();

char ONE = 0x00;
char TWO = 0x00;

void irq_02() {
	while(1);
}

void toPatter1() {
	setpsw_i();
	ONE = 0xaa;
	TWO = 0x55;
	while(1) {
		turnOnLed(ONE);
		delay_s(1);
		turnOnLed(TWO);
		delay_s(1);
	}
}

void toPatter2() {
	setpsw_i();
	ONE = 0xf0;
	TWO = 0x0f;
	while(1) {
		turnOnLed(ONE);
		delay_s(1);
		turnOnLed(TWO);
		delay_s(1);
	}
}
