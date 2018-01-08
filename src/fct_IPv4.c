#include "fct_IPv4.h"



void treatIPv4(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 1;

	if(verbose >= 2)
	{
		printLevelLayer();
		printf("IPv4: ");
	}

	struct iphdr* enteteIP = (struct iphdr*)entete;

	if(verbose == 3)
	{
		printf("\n");
		printLevelLayer();
		printf("Version %d\n",enteteIP->version);
		printLevelLayer();
		printf("IHL %d\n",enteteIP->ihl);
		printLevelLayer();
		printf("TOS %x\n", enteteIP->tos);
		printLevelLayer();
	}

	int len = ntohs(enteteIP->tot_len);
	if(verbose >= 2)
	{
		printf("Total length %d\t",len);

		if(verbose == 3)
		{
			printf("\n");
		}
	}

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Identification %x\n",enteteIP->id);

		printLevelLayer();
		printf("Fragment Offset %x\n",enteteIP->frag_off);

		printLevelLayer();
	}

	if(verbose >= 2)
	{
		printf("TTL %d\t",enteteIP->ttl);

		if(verbose == 3)
		{
			printf("\n");
		}
	}

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Protocol %x\n",enteteIP->protocol);
	}

	if(verbose >= 2)
	{
		printLevelLayer();
		printf("Checksum %x\t",ntohs(enteteIP->check));

		if(verbose == 3)
		{
			printf("\n");
		}
	}

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("Adresse source ");
	printIPv4Addr(enteteIP->saddr);
	printf("\t");

	if(verbose == 3)
	{
		printf("\n");
		printLevelLayer();
	}
	else
	{
		printf("\t");
	}
	printf("Adresse destination ");
	printIPv4Addr(enteteIP->daddr);
	printf("\t");


	if(verbose >= 2)
	{
		printf("\n");
	}

	void* enteteNiv4 = entete+4*enteteIP->ihl;

	switch(enteteIP->protocol)
	{
		case 0x06:
			treatTCP(enteteNiv4,len-4*enteteIP->ihl);
			break;
		case 0x11:
			treatUDP(enteteNiv4);
			break;
		default:
			printLevelLayer();
			printf("Pas de niveau 4");
			break;
	}

}
