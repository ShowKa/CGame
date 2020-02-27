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
	initIRQ();
	setpsw_i();
	while(1) {
		int digi10 = Count_Irq0 / 10;
		int digi1 = Count_Irq0 % 10;
		displayMySeg(digi10);
		displaySegWithIc(digi1);
		delay_ms(200);
	}
}

void initIRQ() {
	// 設定中は最初に割込処理が動かないようにする。
	// interrupt enable=0 => disable
	IEN(ICU, IRQ0) = 0;
	IEN(ICU, IRQ1) = 0;
	// PortDを外部割込の入力端子として開放
	PORTD.PDR.BIT.B0 = 0;
	// port mode register
	// 0=汎用入出力ポート, 1=周辺機能
	PORTD.PMR.BIT.B0 = 0;
	PORTD.PDR.BIT.B1 = 0;
	PORTD.PMR.BIT.B1 = 0;
	// ---
	// pfs
	// ---
	// プロテクト解除
	// Port Write PRotection
	MPC.PWPR.BYTE &= ~0x80;
	MPC.PWPR.BYTE |= 0x40;
	// portDのPFSを有効化
	MPC.PD0PFS.BYTE = 0x40;
	MPC.PD1PFS.BYTE = 0x40;
	// 再プロテクト
	MPC.PWPR.BYTE &= ~0x40;
	MPC.PWPR.BYTE |= 0x80;
	// ---
	// 割り込み関係のレジスタの設定
	// ---
	// IRQ#Control Register の設定
	// 立下りエッジ=プッシュボタンを押した瞬間に割込！
	ICU.IRQCR[0].BIT.IRQMD = 0x01;
	ICU.IRQCR[1].BIT.IRQMD = 0x01;
	// 優先度の設定
	// interup priority register
	IPR(ICU, IRQ0) = 6;
	IPR(ICU, IRQ1) = 6;
	// interupt require フラグクリア
	IR(ICU, IRQ0) = 0x00;
	IR(ICU, IRQ1) = 0x00;
	// interupt require enable
	IEN(ICU, IRQ0) = 1;
	IEN(ICU, IRQ1) = 1;
}