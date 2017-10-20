#include "fct_IPv4.h"

#define IP_ALEN 4

void printIPv4Addr(u_int32_t addr)
{
//	addr = ntohl(addr);
	int i;
	unsigned char octet;

	for(i=0;i<IP_ALEN;i++)
	{
		octet=(unsigned char)addr;
		printf("%d",octet);

		if(i<IP_ALEN-1)
		{
			printf(".");
		}

		addr = addr>>8;
	}	
	printf("\n");
}

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

	printf("Checksum %x\n",enteteIP->check);

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
			break;
		case 0x11:
			treatUDP(enteteNiv4);
			break;
		default:
			printf("Pas de niveau 4");
			break;
	}

}
