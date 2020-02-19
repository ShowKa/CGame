#include "iodefine.h"

void initBuzzer(void);
void initBuzzer(void) {
	//TPU3の動作設定
	//①タイマプリスケーラ（カウント速度）の設定
	TPU3.TCR.BIT.TPSC = 6;	//内部クロック：PCLK/256でカウント
			//46.8757[Hz]で動作（λ=21.33・・・・[uS]) = 1カウント当たり21.33・・・・[uS]
	//②入力クロックエッジ選択ビット（エッジ：入力信号電圧の立上り/立下りの瞬間）
	TPU3.TCR.BIT.CKEG = 1;	//立ち上がりエッジでカウント
	//③カウンタクリア要因選択ビット（カウンタ(TCNT)の初期化条件の設定
	TPU3.TCR.BIT.CCLR = 1;	//TGRAのコンペアマッチ(一致したとき）にクリア（初期化）
	//TMDR（タイマモードレジスタの設定）
	TPU3.TMDR.BIT.MD = 0;	//通常動作設定
	//TGRA（タイマジェネラルレジスタA）の設定
	//仕様として、500[mS]毎にコンペアマッチさせたいとき
	TPU3.TGRA = 10000;	//(100,000[uS] ÷ 21.33・・・・[uS]) - 1 = 4686
	//500[mS]単位でコンペアマッチして、TPU.TSR（タイマステータスレジスタ）のTGFAがON
	//P87動作設定
	// 各デバイスのPFSビットに設定するため、プロテクト解除(P720)
	MPC.PWPR.BIT.B0WI = 0;	// PFSWEのプロテクション解除
	MPC.PWPR.BIT.PFSWE = 1;	// PFSレジスタへの書き込み許可
	PORT2.PMR.BIT.B1 = 1;
	MPC.P21PFS.BIT.PSEL = 3;	// PB7 を TIOCA2 の機能に設定
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

getLength(int length) {

}

static double count = 208;
static double freq = 440.000;
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

void sound(int upDown, int length) {
	double before = freq, after, ratio;
	upDownFreq(upDown);
	after = freq;
	ratio = after / before;
	count = count / ratio;
	TPU3.TCNT = 0;
	TPU3.TGRA = (int) count;
	TPUA.TSTR.BIT.CST3 = 1;
}

