#include "fct_ethernet.h"

void printEthAddr(u_int8_t addr[])
{
	int i=0;

	for(i=0; i<ETH_ALEN ; i++)
	{
		printf("%x",addr[i]);
		if(i<ETH_ALEN-1)
		{
			printf(":");
		}
	}
}


void treatEthernet(void* entete)
{

	struct ether_header* enteteEth = (struct ether_header*)entete;

	printf("Adresse dest\t");
	printEthAddr(enteteEth->ether_dhost);
	printf("\tAdresse src\t");
	printEthAddr(enteteEth->ether_shost);


	printf("\t");
	printf("%x\n",ntohs(enteteEth->ether_type));


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
