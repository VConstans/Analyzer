#include "fct_ethernet.h"
#include "utile.h"



void treatEthernet(void* entete)
{

	struct ether_header* enteteEth = (struct ether_header*)entete;

	printf("Adresse dest\t");
	printEthAddr(enteteEth->ether_dhost);
	printf("Adresse src\t");
	printEthAddr(enteteEth->ether_shost);

	u_int16_t ether_type = ntohs(enteteEth->ether_type);
	printf("%x ",ether_type);	//TODO printf protocole


	//TODO CRC

	void* enteteNiv3;
	enteteNiv3 = entete+sizeof(struct ether_header);

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
}
