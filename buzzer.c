#include "iodefine.h"

void initBuzzer(void);
void initBuzzer1(void);
void initBuzzer2(void);
void initBuzzer(void) {
	initBuzzer1();
	initBuzzer2();
}
void initBuzzer1(void) {
	//�������d�̓��[�h�̉���
	//�����d�̓��[�h�ݒ背�W�X�^�̃v���e�N�g����
	SYSTEM.PRCR.WORD = 0xA503;	//PRKEY[7:0] : �ύX����A5h��ݒ�
				//�N���b�N������H�֘A�F���A���샂�[�h�ݒ�F����
	//TPU�@�\�̏���d�͒ጸ�@�\�̉���
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;	//TPU���j�b�g0(TPU0 - 5)
	//�v���e�N�g�Đݒ�
	SYSTEM.PRCR.WORD = 0xA500;	//PRKEY[7:0] : �ύX����A5h��ݒ�
				//�N���b�N������H�֘A�F�֎~�A���샂�[�h�ݒ�F�֎~
	//-----------------------------------------------------------------------------
	//TPU3�̓���ݒ�
	//1.�^�C�}�v���X�P�[���i�J�E���g���x�j�̐ݒ�
	TPU3.TCR.BIT.TPSC = 3;	//�����N���b�N�F6=PCLK/256, 5=/1024, 3=/64�ŃJ�E���g
			//46.8757[Hz]�œ���i��=21.33�E�E�E�E[uS]) = 1�J�E���g������21.33�E�E�E�E[uS]
	//2.���̓N���b�N�G�b�W�I���r�b�g�i�G�b�W�F���͐M���d���̗����/������̏u�ԁj
	TPU3.TCR.BIT.CKEG = 1;	//�����オ��G�b�W�ŃJ�E���g
	//3.�J�E���^�N���A�v���I���r�b�g�i�J�E���^(TCNT)�̏����������̐ݒ�
	TPU3.TCR.BIT.CCLR = 1;	//TGRA�̃R���y�A�}�b�`(��v�����Ƃ��j�ɃN���A�i�������j
	//TMDR�i�^�C�}���[�h���W�X�^�̐ݒ�j
	TPU3.TMDR.BIT.MD = 0;	//�ʏ퓮��ݒ�
	//TGRA�i�^�C�}�W�F�l�������W�X�^A�j�̐ݒ�
	TPU3.TGRA = 30;
	//--------------------------------------------------------------------------------
	//Port21����ݒ�
	// �e�f�o�C�X��PFS�r�b�g�ɐݒ肷�邽�߁A�v���e�N�g����(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWE�̃v���e�N�V��������
	MPC.PWPR.BIT.PFSWE = 1;	// PFS���W�X�^�ւ̏������݋���
	PORT2.PMR.BIT.B1 = 1;
	MPC.P21PFS.BIT.PSEL = 3;	// PB7 �� TIOCA3 �̋@�\�ɐݒ�
	// �e�f�o�C�X��PFS�r�b�g�ɐݒ�I����̍ăv���e�N�g(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFS���W�X�^�ւ̏������݋���
	MPC.PWPR.BIT.B0WI = 1;	// PFSWE�̃v���e�N�V��������
	TPU3.TIORH.BIT.IOA = 3;
}

// TPU5 �� Port13
void initBuzzer2(void) {
	// �ȃG�l����
	SYSTEM.PRCR.WORD = 0xA503;
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	//TPU9�̓���ݒ�
	TPU5.TCR.BIT.TPSC = 3; //3 => PCLK/64
	TPU5.TCR.BIT.CKEG = 1;
	TPU5.TCR.BIT.CCLR = 1; //TGRA�R���y�A�}�b�`�ݒ�
	TPU5.TMDR.BIT.MD = 0;
	TPU5.TGRA = 30;
	//Port13����ݒ�
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	PORT1.PMR.BYTE = 0xff; // B3=Port13?
	MPC.P13PFS.BIT.PSEL = 3; //3 => TIOCA5
	MPC.PWPR.BIT.PFSWE = 0;	// PFS���W�X�^�ւ̏������݋���
	MPC.PWPR.BIT.B0WI = 1;	// PFSWE�̃v���e�N�V��������
	TPU5.TIOR.BIT.IOA = 3;
}

static double tempo = 60.0;
void setBuzzerTempo(double _tempo);
void setBuzzerTempo(double _tempo) {
	tempo = _tempo;
}

double getLength(int length) {
	// 60�̏ꍇ�Alength=4 -> 1.0�b
	double _length = ((double) length) / 4.0;
	double _tempo = 60.0 / tempo;
	return _length * _tempo;
}

static double count = 832.0; // TPSC=6=/256 => 208.0
static double freq = 440.0;
static const double diff = 1.059463;
static const double diff_7 = 1.50000;
void upDownFreq(int upDown) {
	int i, absolue = upDown > 0 ? upDown : (-1 * upDown),
		sign = upDown > 0 ? 1 : 0;
	for (i = 0; i < absolue; i++) {
		if (sign) {
			freq = freq * diff;
		} else {
			freq = freq / diff;
		}
	}
}

void sound(int upDown, int length);
void sound(int upDown, int length) {
	double before = freq, after, ratio, span;
	upDownFreq(upDown);
	after = freq;
	ratio = after / before;
	count = count / ratio;
	// sound
	TPUA.TSTR.BIT.CST3 = 0;
	TPU3.TCNT = 0;
	TPU3.TGRA = (int) count;
	TPUA.TSTR.BIT.CST3 = 1;
	// length
	span = getLength(length);
	delay_s_dbl(span);
	TPUA.TSTR.BIT.CST3 = 0;
	delay_ms(10);
}

void sound7(int upDown, int length);
void sound7(int upDown, int length) {
	double before = freq, after, ratio, span, other;
	upDownFreq(upDown);
	after = freq;
	ratio = after / before;
	count = count / ratio;
	// sound
	TPUA.TSTR.BIT.CST3 = 0;
	TPU3.TCNT = 0;
	TPU3.TGRA = (int) count;
	TPUA.TSTR.BIT.CST3 = 1;
	// ����7������
	TPUA.TSTR.BIT.CST5 = 0;
	TPU5.TCNT = 0;
	other = count / diff_7;
	TPU5.TGRA = (int) other;
	TPUA.TSTR.BIT.CST5 = 1;
	// length
	span = getLength(length);
	delay_s_dbl(span);
	TPUA.TSTR.BIT.CST3 = 0;
	TPUA.TSTR.BIT.CST5 = 0;
	delay_ms(10);
}

void soundTPU3_TEST(void);
void soundTPU3_TEST(void) {
	// sound
	TPUA.TSTR.BIT.CST3 = 0;
	TPU3.TCNT = 0;
	TPU3.TGRA = (int) count;
	TPUA.TSTR.BIT.CST3 = 1;
	delay_s(5);
	TPUA.TSTR.BIT.CST3 = 0;
}

void soundTPU5_TEST(void);
void soundTPU5_TEST(void) {
	// sound
	TPUA.TSTR.BIT.CST5 = 0;
	TPU5.TCNT = 0;
	TPU5.TGRA = (int) count;
	TPUA.TSTR.BIT.CST5 = 1;
	delay_s(5);
	TPUA.TSTR.BIT.CST5 = 0;
}

