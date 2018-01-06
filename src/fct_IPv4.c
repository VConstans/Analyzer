#include "fct_IPv4.h"
#include "utile.h"



void treatIPv4(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 1;

	printLevelLayer();
	printf("IPv4:\n");

	struct iphdr* enteteIP = (struct iphdr*)entete;

	printLevelLayer();
	printf("Version %d\n",enteteIP->version);
	//TODO verifier qu'il s'agit bien de la version 4 de IP

	printLevelLayer();
	printf("IHL %d\n",enteteIP->ihl);

	printLevelLayer();
	printf("TOS %x\n", enteteIP->tos);

	int len = ntohs(enteteIP->tot_len);
	printLevelLayer();
	printf("Total length %d\n",len);

	printLevelLayer();
	printf("Identification %x\n",enteteIP->id);

	printLevelLayer();
	printf("Fragment Offset %x\n",enteteIP->frag_off);

	printLevelLayer();
	printf("TTL %d\n",enteteIP->ttl);

	printLevelLayer();
	printf("Protocol %x\n",enteteIP->protocol);

	printLevelLayer();
	printf("Checksum %x\n",ntohs(enteteIP->check));

	printLevelLayer();
	printf("Adresse source ");
	printIPv4Addr(enteteIP->saddr);

	printLevelLayer();
	printf("Adresse destination ");
	printIPv4Addr(enteteIP->daddr);

	if(enteteIP->ihl > 5)
	{
		//TODO traitement options
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
