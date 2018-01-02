#include "fct_http.h"

void treatHTTP(void* entete, int len)
{
	printf("=====================>HTTP\n");

	u_int8_t* httpPayload = (u_int8_t*)entete;

	if(!memcmp(httpPayload,"HTTP",4))
	{
		printf("Reply\n");
	}
	else if(!memcmp(httpPayload,"GET",3) || !memcmp(httpPayload,"POST",4) || !memcmp(httpPayload,"HEAD",4))
	{
		printf("Request ");
	}

	int i;
	int affiche = 1;
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

		printf("%c",httpPayload[i]);
	}

	if(affiche)
	{
		for(;i<len;i++)
		{
			printf("%c",httpPayload[i]);
		}
	}
}
