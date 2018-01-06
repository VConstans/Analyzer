#include "fct_UDP.h"

void treatUDP(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 2;

	printLevelLayer();
	printf("UDP:\n");

	struct udphdr* enteteUDP = (struct udphdr*)entete;

	u_int16_t source = ntohs(enteteUDP->source);
	u_int16_t destination = ntohs(enteteUDP->dest);
	u_int16_t lg = ntohs(enteteUDP->len);
	u_int16_t check = ntohs(enteteUDP->check);

	printLevelLayer();
	printf("Port source %d\n",source);
	printLevelLayer();
	printf("Port destination %d\n",destination);
	printLevelLayer();
	printf("Longueur %d\n",lg);
	printLevelLayer();
	printf("Checksum %x\n",check);


	void* enteteNiv7 = entete + sizeof(struct udphdr);


	if(lg > 8)
	{
		//BOOTP
		if(source == 67 || destination == 67 || source == 68 || destination == 68)
		{
			treatBootp(enteteNiv7);
		}

		//DNS
		if(source == 53 || destination == 53)
		{
			treatDNS(enteteNiv7);
		}

		//XXX NAT
	}
}
