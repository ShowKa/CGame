
// �v���g�^�C�v
void irq_01();

// IRQ0 ���荞�݉񐔃J�E���g
int Count_Irq0;

// IRQ0�̊��荞�݉񐔂�seg�ɕ\������
void irq_01() {
	while(1) {
		int digi10 = Count_Irq0 / 10;
		int digi1 = Count_Irq0 % 10;
		displayMySeg(digi10);
		displaySegWithIc(digi1);
		delay_ms(200);
	}
}
