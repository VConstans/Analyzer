#include "fct_ftp.h"

void treatFTP(void* entete, int len)
{
	printf("==================>ftp %d\n",len);

	u_int8_t* messageFTP = (u_int8_t*)entete;

	if(*messageFTP >= 0x30 && *messageFTP <=0x39)
	{
		printf("Response\n");
		printf("Response code: ");
		printf("%c",messageFTP[0]);
		printf("%c",messageFTP[1]);
		printf("%c",messageFTP[2]);
		printf("\n");

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
		printf("Request\n");
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
		for(i=0;i<len;i++)
		{
			printf("%c",*messageFTP);
			messageFTP++;
		}
	}
}
