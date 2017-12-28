#include "fct_http.h"

void treatHTTP(void* entete, int len)
{
	printf("=====================>HTTP\n");


	u_int8_t* httpPayload = (u_int8_t*)entete;
	printHexToAscii_len(len,httpPayload);
}
