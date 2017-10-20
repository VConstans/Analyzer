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


void treatEthernet(struct ether_header* entete)
{
	printf("Adresse dest\t");
	printEthAddr(entete->ether_dhost);
	printf("\tAdresse src\t");
	printEthAddr(entete->ether_shost);


	printf("\t");
	printf("%x\n",ntohs(entete->ether_type));

	struct iphdr* enteteIP;

	switch(entete->ether_type)
	{
		case 0x0008:
			enteteIP = (struct iphdr*)((void*)entete+sizeof(struct ether_header));
			treatIPv4(enteteIP);
			break;
		case 0xdd86:
			//treatIPv6(enteteIP);
			break;
		default:
			printf("Pas de couche 3");
	}
}
