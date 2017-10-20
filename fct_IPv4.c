#include "fct_IPv4.h"

void printIPv4Addr(u_int32_t addr)
{
	int i;
	char octet;

	for(i=0;i<4;i++)
	{
		octet=(char)addr;
		printf("%d.",octet);
		addr>>8;
	}	
}

void treatIPv4(struct ip* entete)
{
	printf("Version %d\n",entete->ip_v);

	int taille_entete = entete->ip_hl;
	printf("IHL %d\n",taille_entete);


	printf("TOS %x\n", entete->ip_tos);

	printf("Total length %d\n",entete->ip_len);

	printf("Identification %x\n",entete->ip_id);

	printf("Fragment Offset %x\n",entete->ip_off);

	printf("TTL %d\n",entete->ip_ttl);

	printf("Protocol %x\n",entete->ip_p);

	printf("Checksum %x\n",entete->ip_sum);

	printf("Adresse source ");

//	printIPv4Addr(entete->saddr);

	printf("\n");
}
