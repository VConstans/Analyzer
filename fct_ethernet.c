#include "fct_ethernet.h"
#include "utile.h"



void treatEthernet(void* entete)
{

	struct ether_header* enteteEth = (struct ether_header*)entete;

	printf("Adresse dest\t");
	printEthAddr(enteteEth->ether_dhost);
	printf("Adresse src\t");
	printEthAddr(enteteEth->ether_shost);


	printf("%x\n",ntohs(enteteEth->ether_type));	//TODO printf protocole


	//TODO CRC

	void* enteteNiv3;

	switch(enteteEth->ether_type)
	{
		case 0x0008:
			enteteNiv3 = entete+sizeof(struct ether_header);
			treatIPv4(enteteNiv3);
			break;
		case 0xdd86:
			//treatIPv6(enteteIP);
			break;
		default:
			printf("Pas de couche 3");
	}
}
