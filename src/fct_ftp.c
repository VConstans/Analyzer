#include "fct_ftp.h"

void treatFTP(void* entete, int len)
{
	printf("==================>ftp\n");
	printf("=========>len %d\n",len);

	u_int8_t* enteteFTP = (u_int8_t*)entete;
	
	printHexToAscii_len(len,enteteFTP);
}
