#include "fct_IPv4.h"

void treatIPv4(struct iphdr* entete)
{
	printf("Version %x\n",entete->version);

	int taille_entete = entete->ihl;
	printf("IHL %x\n",taille_entete);

	printf("Protocol %x",entete->protocol);
}
