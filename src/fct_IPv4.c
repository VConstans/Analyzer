#include "fct_IPv4.h"
#include "utile.h"



void treatIPv4(void* entete)
{

	struct iphdr* enteteIP = (struct iphdr*)entete;

	printf("Version %d\n",enteteIP->version);

	printf("IHL %d\n",enteteIP->ihl);

	printf("TOS %x\n", enteteIP->tos);

	printf("Total length %d\n",enteteIP->tot_len);

	printf("Identification %x\n",enteteIP->id);

	printf("Fragment Offset %x\n",enteteIP->frag_off);

	printf("TTL %d\n",enteteIP->ttl);

	printf("Protocol %x\n",enteteIP->protocol);

	printf("Checksum %x\n",ntohs(enteteIP->check));

	printf("Adresse source ");

	printIPv4Addr(enteteIP->saddr);

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
			treatTCP(enteteNiv4,enteteIP->tot_len-4*enteteIP->ihl);
			break;
		case 0x11:
			treatUDP(enteteNiv4);
			break;
		default:
			printf("Pas de niveau 4");
			break;
	}

}
