#include "fct_smtp.h"

void treatSMTP(void* entete, int len)
{
	printLevelLayer();
	printf("SMTP:\n");
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 3;

	u_int8_t* smtpPayload = (u_int8_t*)entete;
/*
	int i = 0;

	struct listAffichage* listAffichage = getAffichage(...)

	if(listAffichage->in_data)
	{
		if(!memcmp(&smtpPayload[0],".\r\n",3))
		{
			listAffichage->affichage = 1;
			listAffichage->in_data = 0;
		}
		else
		{
			for(i=0;i<len;i++)
			{
				if(listAffichage->affichage)
				{
					printf("%c",smtpPayload[i]);
				}
			}
		}
	}
	else
	{





		if(smtpPayload[0] >= '0' && smtpPayload[0] <= '9')
		{
			printf("Reply code: %c%c%c\n",smtpPayload[0],smtpPayload[1],smtpPayload[2]);
			i = 3;
			//TODO reply message
		}
		else
		{
			printf("Request: ");
			while(smtpPayload[i] != ' ')
			{
				printf("%c",smtpPayload[i]);
				i++;
			}
			printf("\n");
		}


		for(;i<len;i++)
		{
			if(smtpPayload[i] == '\n')
			{
				if(!memcmp(&smtpPayload[i+1],"Content-Type: ",14))
				{
					if(memcmp(&smtpPayload[i+15],"text",4)!= 0)
					{
						setAffichage(listAffichage,port,sens,0);
					}
				}
				if(!memcmp(&smtpPayload[i+1],"Content-Transfer-Encoding: ",18))
				{
					if(memcmp(&smtpPayload[19],"8bit",4))
					{
						setAffichage(listAffichage,port,sens,0);
					}
				}
				
			}

			if(!memcmp(&smtpPayload[0],"DATA",4))
			{
				setDataAffichage(listAffichage,port,sens,1);
			}

			printf("%c",smtpPayload[i]);
		}
	}*/
}
