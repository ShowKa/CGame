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

void main(void);
void main(void)
{
	int i;
	char a = 0x41;
	// setup
	initPDR();
	initBuzzer();
	init_TIMER();
	LCD_init();
	// do something
	for (i = 0; i < 26; i++) {
		LCD_locate_1st(i+1);
		LCD_putchar(a++);
		delay_s(1);
	}
	// end
	keepGate();
}
