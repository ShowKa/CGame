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
#include <machine.h>
#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

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
	// interruption
	initIRQ();
	init_CMT0();
	setpsw_i();
	// do something
	game();
	// end
	keepGate();
}
