/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

#include "iodefine.h"
#include <machine.h>
#include "vect.h"

void main(void);
void main(void)
{
	// setup
	initPDR();
	initBuzzer();
	init_TIMER();
	init_TPU8();
	init_TPU9();
	LCD_init();
	// CMT����
	init_CMT0();
	// I����
	initIRQ();
	// ���荞�݋���
	// psw:ProsessorStatusWord
	// ���荞�݋��r�b�g(I�r�b�g�j��ݒ�
	// ���̃��W�X�^�͐�p�֐����K�v�B
	setpsw_i();
	// do something
	while(1);
	// end
	keepGate();
}
