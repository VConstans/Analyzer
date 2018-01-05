#include "fct_smtp.h"

void treatSMTP(void* entete, int len)
{
	printf("===============>smtp\n");
	extern int levelPrinting;
	levelPrinting = 3;

	u_int8_t* smtpPayload = (u_int8_t*)entete;

	if(smtpPayload[0] >= '0' && smtpPayload[0] <= '9')
	{
		printf("Reply\n");
	}
	else
	{
		printf("Request ");
	}


	int i = 0;
	int affiche = 0;

	struct 

	if(enteteHTTP)
	{
		affiche = 1;
		for(i=0;i<len;i++)
		{
			if(smtpPayload[i] == '\n')
			{
				if(!memcmp(&smtpPayload[i+1],"Content-Type: ",14))
				{
					if(memcmp(&smtpPayload[i+15],"text",4)!= 0)
					{
						affiche = 0;
						//TODO set
					}
				}
				if(!memcmp(&smtpPayload[i+1],"Content-Transfer-Encoding: ",18))
				{
					if(memcmp(&smtpPayload[19],"8bit",4))
					{
						affiche = 0;
						//TODO set
					}
				}
				
			}

			if(smtpPayload[i] == '\r')
			{
				if(!memcmp(&smtpPayload[i],"\r\n\r\n",4))
				{
					break;
				}
			}

			printf("%c",smtpPayload[i]);
		}
	}
}
