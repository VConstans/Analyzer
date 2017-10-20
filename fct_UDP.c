#include "fct_UDP.h"

void treatUDP(void* entete)
{
	struct udphdr* enteteUDP = (struct udphdr*)entete;

	printf("Port source %u\n",enteteUDP->source);
	printf("Port destination %u\n",enteteUDP->dest);
	printf("Longueur %u\n",enteteUDP->len);
	printf("Checksum %u\n",enteteUDP->check);


	void* enteteNiv7 = entete + sizeof(struct udphdr);

	//BOOTP
	if(enteteUDP->source == 67 || enteteUDP->dest == 67 || enteteUDP->source == 68 || enteteUDP->dest == 68)
	{
		treatBootp(enteteNiv7);
	}

	//DNS
	if(enteteUDP->source == 53 || enteteUDP->dest == 53)
	{
		//treatDNS(enteteNiv7);
	}

	//XXX NAT

}
