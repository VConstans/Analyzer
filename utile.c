#include "utile.h"


#define IP_ALEN 4

void printIPv4Addr(u_int32_t addr)
{
//	addr = ntohl(addr);
	int i;
	unsigned char octet;

	for(i=0;i<IP_ALEN;i++)
	{
		octet=(unsigned char)addr;
		printf("%d",octet);

		if(i<IP_ALEN-1)
		{
			printf(".");
		}

		addr = addr>>8;
	}	
	printf("\n");
}


void printEthAddr(u_int8_t addr[])
{
	int i=0;

	for(i=0; i<ETH_ALEN ; i++)
	{
		printf("%x",addr[i]);
		if(i<ETH_ALEN-1)
		{
			printf(":");
		}
	}
	printf("\n");
}
