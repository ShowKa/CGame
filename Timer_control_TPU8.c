#include "iodefine.h"

void init_TPU8(void);
void start_TPU8(void);
void stop_TPU8(void);
void wait_TPU8(void);


void init_TPU8(void)
{
	//プロテクトの解除
	SYSTEM.PRCR.WORD = 0xA503;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：許可、動作モード等：許可
	//TPU機能の消費電力低減機能解除
	SYSTEM.MSTPCRA.BIT.MSTPA12 = 0;	// TPUユニット1(TPU6 - 11)
	//プロテクトの設定
	SYSTEM.PRCR.WORD = 0xA500;  // PRKEY[7:0] : 書き換え時はA5hを設定
                        // クロック発生回路関連：禁止、動作モード等：禁止
	//TPU0の動作設定
	//�@タイマプリスケーラ(カウント速度)の設定
	TPU8.TCR.BIT.TPSC = 7;	//内部クロック：PCLK/1024でカウント
						//46,875[Hz]で動作(λ=21.333333・・・・・[uS]) = 1カウントあたり21.33333・・・・・[uS]
	//�A入力クロックエッジ選択ビット(エッジ：入力信号電圧の立上がり/立下りの瞬間)
	TPU8.TCR.BIT.CKEG = 1;	//立ち上がりエッジでカウント
	//�Bカウンタクリア要因選択ビット(カウンタ(TCNT)の初期化条件の設定
	TPU8.TCR.BIT.CCLR = 1;	//TGRAとコンペアマッチ(一致したとき)にクリア（初期化）
	//TMDR（タイマモードレジスタ）の設定
	TPU8.TMDR.BIT.MD = 0;	//通常動作設定
	//TGRAの設定（1秒)
	TPU8.TGRA = 46874;
		//TGRAの設定（1秒)
	//TPU8.TGRA = 6;
}

void start_TPU8(void) {
	TPUB.TSTR.BIT.CST8 = 1;
}

void stop_TPU8(void) {
	TPUB.TSTR.BIT.CST8 = 0;
}

void wait_TPU8(void) {
	while(TPU8.TSR.BIT.TGFA == 0);
	TPU8.TSR.BIT.TGFA = 0;
}