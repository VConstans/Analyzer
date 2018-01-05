#include "fct_http.h"

void treatHTTP(void* entete, int len)
{
	extern int levelPrinting;
	levelPrinting = 3;

	printf("=====================>HTTP\n");

	u_int8_t* httpPayload = (u_int8_t*)entete;
	int enteteHTTP = 0;

	if(!memcmp(httpPayload,"HTTP",4))
	{
		printf("Reply\n");
		enteteHTTP = 1;
	}
	else if(!memcmp(httpPayload,"GET",3) || !memcmp(httpPayload,"POST",4) || !memcmp(httpPayload,"HEAD",4))
	{
		printf("Request ");
		enteteHTTP = 1;
	}


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
/*
				if(!memcmp(&httpPayload[i+1],"Content-Length: ",16))
				{
					int j=i+17;
					while(httpPayload[j] != '\r')
					{
						j++;
					}
					httpPayload[j] = '\0';
					int length = atoi(httpPayload[i+17]);
					setLength(listLength,id,length);
					httpPayload[j] = '\r';
				}*/
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
	}

//	struct listLength* maillonLength = getLength(listLength,id);
	if(affiche)	//TODO  tenir compte de content len
	{
		for(;i<len;i++)
		{
				printf("%c",httpPayload[i]);
		}
//		maillonLength->length--;
	}
}
