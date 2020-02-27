#include "iodefine.h"
#include <machine.h>
#include "vect.h"

// �v���g�^�C�v
void irq_01();
void initIRQ();

// IRQ0 ���荞�݉񐔃J�E���g
int Count_Irq0;

// IRQ0�̊��荞�݉񐔂�seg�ɕ\������
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
	// �ݒ蒆�͍ŏ��Ɋ��������������Ȃ��悤�ɂ���B
	// interrupt enable=0 => disable
	IEN(ICU, IRQ0) = 0;
	IEN(ICU, IRQ1) = 0;
	// PortD���O�������̓��͒[�q�Ƃ��ĊJ��
	PORTD.PDR.BIT.B0 = 0;
	// port mode register
	// 0=�ėp���o�̓|�[�g, 1=���Ӌ@�\
	PORTD.PMR.BIT.B0 = 0;
	PORTD.PDR.BIT.B1 = 0;
	PORTD.PMR.BIT.B1 = 0;
	// ---
	// pfs
	// ---
	// �v���e�N�g����
	// Port Write PRotection
	MPC.PWPR.BYTE &= ~0x80;
	MPC.PWPR.BYTE |= 0x40;
	// portD��PFS��L����
	MPC.PD0PFS.BYTE = 0x40;
	MPC.PD1PFS.BYTE = 0x40;
	// �ăv���e�N�g
	MPC.PWPR.BYTE &= ~0x40;
	MPC.PWPR.BYTE |= 0x80;
	// ---
	// ���荞�݊֌W�̃��W�X�^�̐ݒ�
	// ---
	// IRQ#Control Register �̐ݒ�
	// ������G�b�W=�v�b�V���{�^�����������u�ԂɊ����I
	ICU.IRQCR[0].BIT.IRQMD = 0x01;
	ICU.IRQCR[1].BIT.IRQMD = 0x01;
	// �D��x�̐ݒ�
	// interup priority register
	IPR(ICU, IRQ0) = 6;
	IPR(ICU, IRQ1) = 6;
	// interupt require �t���O�N���A
	IR(ICU, IRQ0) = 0x00;
	IR(ICU, IRQ1) = 0x00;
	// interupt require enable
	IEN(ICU, IRQ0) = 1;
	IEN(ICU, IRQ1) = 1;
}