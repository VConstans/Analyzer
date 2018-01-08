#include "fct_ftp.h"

void treatFTP(void* entete, int len)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 3;

	if(verbose >= 2)
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("FTP:");
		if(verbose ==3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}

	u_int8_t* messageFTP = (u_int8_t*)entete;

	if(*messageFTP >= 0x30 && *messageFTP <=0x39)
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Response ");
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("%c",messageFTP[0]);
		printf("%c",messageFTP[1]);
		printf("%c",messageFTP[2]);
		if(verbose == 3)
		{
			printf("\n");
			printLevelLayer();
		}


		if(verbose == 3)
		{		
			if(messageFTP[3] != 0x20)
			{
				printf("Error ftp format message\n");
			}
			else
			{
				u_int8_t* curseur = &messageFTP[4];

				int i;
				for(i=0;i<len-4;i++)
				{
					printf("%c",*curseur);
					curseur++;
				}
			}
		}
	}
	else
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Request");
		if(verbose ==3)
		{
			printf("\n");
			printLevelLayer();
		}
		else
		{
			printf("\t");
		}

		while(*messageFTP != 0x20)
		{
			printf("%c",*messageFTP);
			messageFTP++;
			len--;

			if(*messageFTP == 0x0d && *(messageFTP+1) == 0x0a)
			{
				len--;
				break;
			}
		}
		len--;
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}

		if(verbose == 3)
		{
			int i;
			printLevelLayer();
			for(i=0;i<len;i++)
			{
				printf("%c",*messageFTP);
				messageFTP++;
			}
		}
	}
}
