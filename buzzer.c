#include "iodefine.h"

void initBuzzer(void);
void initBuzzer(void) {
	//★低消費電力モードの解除
	//低消費電力モード設定レジスタのプロテクト解除
	SYSTEM.PRCR.WORD = 0xA503;	//PRKEY[7:0] : 変更時はA5hを設定
				//クロック発生回路関連：許可、動作モード設定：許可
	//TPU機能の消費電力低減機能の解除
	SYSTEM.MSTPCRA.BIT.MSTPA13 = 0;	//TPUユニット0(TPU0 - 5)
	//プロテクト再設定
	SYSTEM.PRCR.WORD = 0xA500;	//PRKEY[7:0] : 変更時はA5hを設定
				//クロック発生回路関連：禁止、動作モード設定：禁止
	//-----------------------------------------------------------------------------
	//TPU3の動作設定
	//1.タイマプリスケーラ（カウント速度）の設定
	TPU3.TCR.BIT.TPSC = 6;	//内部クロック：6=PCLK/256, 5=PCLK/1024でカウント
			//46.8757[Hz]で動作（λ=21.33・・・・[uS]) = 1カウント当たり21.33・・・・[uS]
	//2.入力クロックエッジ選択ビット（エッジ：入力信号電圧の立上り/立下りの瞬間）
	TPU3.TCR.BIT.CKEG = 1;	//立ち上がりエッジでカウント
	//3.カウンタクリア要因選択ビット（カウンタ(TCNT)の初期化条件の設定
	TPU3.TCR.BIT.CCLR = 1;	//TGRAのコンペアマッチ(一致したとき）にクリア（初期化）
	//TMDR（タイマモードレジスタの設定）
	TPU3.TMDR.BIT.MD = 0;	//通常動作設定
	//TGRA（タイマジェネラルレジスタA）の設定
	TPU3.TGRA = 30;
	//--------------------------------------------------------------------------------
	//P21動作設定
	// 各デバイスのPFSビットに設定するため、プロテクト解除(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWEのプロテクション解除
	MPC.PWPR.BIT.PFSWE = 1;	// PFSレジスタへの書き込み許可
	PORT2.PMR.BIT.B1 = 1;
	MPC.P21PFS.BIT.PSEL = 3;	// PB7 を TIOCA3 の機能に設定
	// 各デバイスのPFSビットに設定終了後の再プロテクト(P720)
	MPC.PWPR.BIT.PFSWE = 0;	// PFSレジスタへの書き込み許可
	MPC.PWPR.BIT.B0WI = 1;	// PFSWEのプロテクション解除
	TPU3.TIORH.BIT.IOA = 3;
}

static double tempo = 60.0;
void setBuzzerTempo(double _tempo);
void setBuzzerTempo(double _tempo) {
	tempo = _tempo;
}

double getLength(int length) {
	// 60の場合、length=4 -> 1.0秒
	double _length = ((double) length) / 4.0;
	double _tempo = 60.0 / tempo;
	return _length * _tempo;
}

static double count = 208.0;
static double freq = 440.0;
static const double diff = 1.059463;
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

