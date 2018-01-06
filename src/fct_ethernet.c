#include "fct_ethernet.h"


void treatEthernet(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 0;

	printLevelLayer();
	printf("ETHERNET:\n");

	struct ether_header* enteteEth = (struct ether_header*)entete;

	printLevelLayer();
	printf("Adresse dest\t");
	printLevelLayer();
	printEthAddr(enteteEth->ether_dhost);
	printLevelLayer();
	printf("Adresse src\t");
	printLevelLayer();
	printEthAddr(enteteEth->ether_shost);

	u_int16_t ether_type = ntohs(enteteEth->ether_type);
	printLevelLayer();
	printf("EtherType: ");
	printLevelLayer();
	printf("%x ",ether_type);	//TODO printf protocole


	//TODO CRC

	void* enteteNiv3;
	enteteNiv3 = entete+sizeof(struct ether_header);
	printLevelLayer();

	switch(ether_type)
	{
		case 0x0800:
			printf("IPv4\n");
			treatIPv4(enteteNiv3);
			break;
		case 0x86dd:
			printf("IPv6\n");
			treatIPv6(enteteNiv3);
			break;
		case 0x0806:
			printf("ARP\n");
			treatARP(enteteNiv3);
			break;
		default:
			printf("Pas de couche 3");
	}


	printf("\n\n");
}
