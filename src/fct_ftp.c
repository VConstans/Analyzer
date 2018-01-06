#include "fct_ftp.h"

void treatFTP(void* entete, int len)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 3;

	printLevelLayer();
	printf("FTP:\n");

	u_int8_t* messageFTP = (u_int8_t*)entete;

	if(*messageFTP >= 0x30 && *messageFTP <=0x39)
	{
		printLevelLayer();
		printf("Response\n");
		printLevelLayer();
		printf("Response code: ");
		printf("%c",messageFTP[0]);
		printf("%c",messageFTP[1]);
		printf("%c",messageFTP[2]);
		printf("\n");


		printLevelLayer();
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
	else
	{
		printLevelLayer();
		printf("Request\n");
		printLevelLayer();
		printf("Request Command: ");

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
		printf("\n");

		int i;
		printLevelLayer();
		for(i=0;i<len;i++)
		{
			printf("%c",*messageFTP);
			messageFTP++;
		}
	}
}
