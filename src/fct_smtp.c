#include "fct_smtp.h"

void treatSMTP(void* entete, int len)
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
		printf("SMTP:");
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}


	u_int8_t* smtpPayload = (u_int8_t*)entete;

	int i;
	int affiche = 1;


	if(smtpPayload[0] >= '0' && smtpPayload[0] <= '9')
	{
		printf("Reply code: %c%c%c",smtpPayload[0],smtpPayload[1],smtpPayload[2]);
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
		//TODO reply message
	}
	else
	{
		i = 0;
		printf("Request: ");
		while(smtpPayload[i] != ' ')
		{
			printf("%c",smtpPayload[i]);
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
	}


	if(verbose >= 2)
	{
		for(i=0;i<len;i++)
		{
			if(smtpPayload[i] == '\n')
			{
				if(!memcmp(&smtpPayload[i+1],"Content-Type: ",14))
				{
					if(memcmp(&smtpPayload[i+15],"text",4)!= 0)
					{
						affiche = 0;
					}
				}
				if(!memcmp(&smtpPayload[i+1],"Content-Transfer-Encoding: ",18))
				{
					if(memcmp(&smtpPayload[19],"8bit",4))
					{
						affiche = 0;
					}
				}
				
			}

			if(!memcmp(&smtpPayload[i],"DATA",4))
			{
				break;
			}

			printHexToAscii(smtpPayload[i]);
		}

		if(verbose == 3)
		{
			if(affiche)
			{
				for(;i<len;i++)
				{
					printf("%c",smtpPayload[i]);
				}
			}
		}
	}
}
