
// プロトタイプ
void irq_01();

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
