#include "fct_smtp.h"

void treatSMTP(void* entete, int len)
{
	extern int levelPrinting;
	levelPrinting = 3;

	u_int8_t* enteteSMTP = (u_int8_t*)entete;

	printHexToAscii_len(len,enteteSMTP);
}
