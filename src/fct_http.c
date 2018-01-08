#include "fct_http.h"

void treatHTTP(void* entete, int len)
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
		printf("HTTP:");
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}

	u_int8_t* httpPayload = (u_int8_t*)entete;
	int enteteHTTP = 0;

	if(!memcmp(httpPayload,"HTTP",4))
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Reply");
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
		enteteHTTP = 1;
	}
	else if(!memcmp(httpPayload,"GET",3) || !memcmp(httpPayload,"POST",4) || !memcmp(httpPayload,"HEAD",4))
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Request");
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
		enteteHTTP = 1;
	}


	if(verbose >= 2)
	{
		int i = 0;
		int affiche = 0;
		if(enteteHTTP)
		{
			affiche = 1;
			for(i=0;i<len;i++)
			{
				if(httpPayload[i] == '\n')
				{
					if(!memcmp(&httpPayload[i+1],"Content-Type: ",14))
					{
						if(memcmp(&httpPayload[i+15],"text",4)!= 0)
						{
							affiche = 0;
						}
					}
					if(!memcmp(&httpPayload[i+1],"Content-Encoding: ",18))
					{
						affiche = 0;
					}
				}

				if(httpPayload[i] == '\r')
				{
					if(!memcmp(&httpPayload[i],"\r\n\r\n",4))
					{
						break;
					}
				}

				if(httpPayload[i-1] == '\n')
				{
					printLevelLayer();
				}

				printHexToAscii(httpPayload[i]);
			}
		}

		if(verbose == 3)
		{
			if(affiche)
			{
				for(;i<len;i++)
				{
						printf("%c",httpPayload[i]);
				}
			}
		}
	}
}
