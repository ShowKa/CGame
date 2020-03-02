#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// プロトタイプ
void irq_01();
void initIRQ();

// IRQ0 割り込み回数カウント
int Count_Irq0;

// IRQ0の割り込み回数をsegに表示する
void irq_01() {
	while(1) {
		int digi10 = Count_Irq0 / 10;
		int digi1 = Count_Irq0 % 10;
		displayMySeg(digi10);
		displaySegWithIc(digi1);
		delay_ms(200);
	}
}

void initIRQ() {
	IEN(ICU, IRQ0) = 0;
	IEN(ICU, IRQ1) = 0;
	// PORTをIRQとして設定
	PORTD.PDR.BIT.B0 = 0;
	PORTD.PMR.BIT.B0 = 0;
	PORTD.PDR.BIT.B1 = 0;
	PORTD.PMR.BIT.B1 = 0;
	
	// プロテクト解除
	MPC.PWPR.BYTE &= ~0x80;
	MPC.PWPR.BYTE |= 0x40;
	
	MPC.PD0PFS.BYTE = 0x40;
	MPC.PD1PFS.BYTE = 0x40;
	
	// 再プロテクト
	MPC.PWPR.BYTE &= ~0x40;
	MPC.PWPR.BYTE |= 0x80;
	
	// IRQの設定
	ICU.IRQCR[0].BIT.IRQMD = 0x01;
	ICU.IRQCR[1].BIT.IRQMD = 0x01;
	
	// 優先度の設定
	IPR(ICU, IRQ0) = 6;
	IPR(ICU, IRQ1) = 6;
	
	IR(ICU, IRQ0) = 0x00;
	IR(ICU, IRQ1) = 0x00;
	
	IEN(ICU, IRQ0) = 1;
	IEN(ICU, IRQ1) = 1;

}