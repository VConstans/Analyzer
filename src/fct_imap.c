#include "fct_imap.h"

void treatIMAP(void* entete,int len)
{
	extern int levelPrinting;
	levelPrinting = 3;
	extern int verbose;

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("IMAP:");
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}

	u_int8_t* imapPayload = (u_int8_t*)entete;

	int i = 0;
	if(imapPayload[0] == '*')
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Reply: ");
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}
	else
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}

		if(verbose >= 2)
		{
			printf("Tag: ");
		}
		while(imapPayload[i] != ' ')
		{
			if(verbose >= 2)
			{
				printf("%c",imapPayload[i]);
				if(verbose == 3)
				{
					printf("\n");
				}
				else
				{
					printf("\t");
				}
			}
			i++;
		}
		i++;
		if(!memcmp(&imapPayload[i],"OK",2) ||!memcmp(&imapPayload[i],"NO",2) ||!memcmp(&imapPayload[i],"BAD",3))
		{
			printf("Reply: ");
		}
		else
		{
			printf("Command: ");
		}
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}


	if(verbose == 3)
	{
		for(i=0;i<len;i++)
		{
			printHexToAscii(imapPayload[i]);
		}
	}
}
