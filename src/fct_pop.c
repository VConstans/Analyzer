#include "fct_pop.h"

void treatPOP(void* entete,int len)
{
	extern int levelPrinting;
	levelPrinting = 3;
	extern int verbose;

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("POP:");
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}

	u_int8_t* popPayload = (u_int8_t*)entete;

	int i;
	if(popPayload[0] == '+')
	{
		printf("Reply: ");
		i = 1;
	}
	else
	{
		printf("Command: ");
		i=0;
	}

	while(popPayload[i] != ' ')
	{
		printf("%c",popPayload[i]);
		i++;
	}
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}

	if(verbose >= 2)
	{
		for(;i<len;i++)
		{
			printHexToAscii(popPayload[i]);
		}
	}
}
