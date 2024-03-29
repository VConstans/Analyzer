#include "fct_ethernet.h"

void treatEthernet(void* entete)
{
	extern int verbose;

	if(verbose >= 2)
	{
		printf("Ethernet: ");
	}

	struct ether_header* enteteEth = (struct ether_header*)entete;
	u_int16_t ether_type = ntohs(enteteEth->ether_type);

	if(verbose >=2 || (ether_type != 0x0800 && ether_type != 0x86dd))
	{
		printf("Destination Address: ");
		printEthAddr(enteteEth->ether_dhost);
		printf("\tSource Address: ");
		printEthAddr(enteteEth->ether_shost);
		printf("\t");

	}

	//Ether Type
	if(verbose >= 2)
	{
		printf("EtherType: ");
		printf("%x ",ether_type);
	}


	//Debut de l'entete de niveau 3
	void* enteteNiv3;
	enteteNiv3 = entete+sizeof(struct ether_header);
	

	//Appelle de la bonne fonction de couche 3 selon l'ether type
	switch(ether_type)
	{
		//IPv4
		case 0x0800:
			if(verbose >= 2)
			{
				printf("IPv4");
			}
			if(verbose == 3)
			{
				printf("\n");
			}
			treatIPv4(enteteNiv3);
			break;
		//IPv6
		case 0x86dd:
			if(verbose >= 2)
			{
				printf("IPv6");
			}
			if(verbose == 3)
			{
				printf("\n");
			}
			treatIPv6(enteteNiv3);
			break;
		//ARP
		case 0x0806:
			if(verbose >= 2)
			{
				printf("ARP");
			}
			if(verbose == 3)
			{
				printf("\n");
			}
			treatARP(enteteNiv3);
			break;
		default:
			printf("Pas de couche 3");
	}


	printf("\n\n");
}

