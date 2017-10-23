#include "fct_bootp.h"

void treatBootp(void* entete)
{
	struct bootp* enteteB = (struct bootp*)entete;

	if(*((unsigned long*)(enteteB->bp_vend)) == 0x63825663)
	{
		printf("Bootp\n");
	}
}
