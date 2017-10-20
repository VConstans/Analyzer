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
}

void treatIPv4(struct iphdr* entete)
{
	printf("Version %d\n",entete->version);

	int taille_entete = entete->ihl;
	printf("IHL %d\n",taille_entete);


	printf("TOS %x\n", entete->tos);

	printf("Total length %d\n",entete->tot_len);

	printf("Identification %x\n",entete->id);

	printf("Fragment Offset %x\n",entete->frag_off);

	printf("TTL %d\n",entete->ttl);

	printf("Protocol %x\n",entete->protocol);

	printf("Checksum %x\n",entete->check);

	printf("Adresse source ");

	printIPv4Addr(entete->saddr);

	printf("\n");
}
