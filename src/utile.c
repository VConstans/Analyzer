#include "utile.h"


#define IP_ALEN 4

extern int verbose;

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
}

void printIPv4Addr_u_int8(u_int8_t* addr)
{
//	addr = ntohl(addr);
	int i;
	unsigned char octet;

	for(i=0;i<IP_ALEN;i++)
	{
		octet=(unsigned char)(*addr);
		printf("%d",octet);

		if(i<IP_ALEN-1)
		{
			printf(".");
		}

		addr = addr+1;
	}	
}


void printIPv6Addr(uint8_t* addr)
{
	int i;
	for(i=0;i<16;i+=2)
	{
		printf("%x%x",addr[i],addr[i+1]);

		if(i+1 != 15)
		{
			printf(":");
		}
	}
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
}


void printLevelLayer()
{
	extern int levelPrinting;
	int i;
	for(i=0;i<levelPrinting;i++)
	{
		printf("\t");
	}
}

void printHexToAscii(u_int8_t car)
{
	switch(car)
	{
		case 0x0a:
			printf("\n");
			break;
		case 0x0d:
			break;
		default:
			printf("%c",car);
	}
}


void printfAlign(char* string)
{
	printLevelLayer();

	printf("%s",string);
}

void printHexToAscii_len(int len, u_int8_t* string)
{
	printLevelLayer();

	int i = 0;
	
	for(i=0;i<len;i++)
	{
		printHexToAscii(string[i]);
	}

	printf("\n");
}
