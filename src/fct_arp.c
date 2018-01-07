#include "fct_arp.h"

void treatARP(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 1;

	if(verbose == 3)
	{
		printLevelLayer();
	}
	if(verbose >= 2)
	{
		printf("ARP: ");
	}
	if(verbose == 3)
	{
		printf("\n");
	}

	struct arphdr* enteteARP = (struct arphdr*)entete;

	uint16_t hrd = ntohs(enteteARP->ar_hrd);
	uint16_t pro = ntohs(enteteARP->ar_pro);
	uint8_t hln = enteteARP->ar_hln;
	uint8_t pln = enteteARP->ar_pln;
	uint16_t op = ntohs(enteteARP->ar_op);

	switch(op)
	{
		case ARPOP_REQUEST:
			printLevelLayer();
			printf("ARP Request");
			break;
		case ARPOP_REPLY:
			printLevelLayer();
			printf("ARP Reply");
			break;
	}
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Hardware type: %d ",hrd);

		switch(hrd)
		{
			case ARPHRD_ETHER:
				printf("Ethernet");
				break;

			//TODO autre cas
			//TODO default
		}
		printf("\n");


		printLevelLayer();
		printf("Protocol type: %d ",pro);
		switch(pro)
		{
			case 0x800:
				printf("IP");
				break;
			//TODO default
		}
		printf("\n");

		printLevelLayer();
		printf("Hardware length: %d ",hln);
		switch(hln)
		{
			case 6:
				printf("Ethernet");
				break;

			//TODO autre cas
			//TODO default
		}
		printf("\n");


		printLevelLayer();
		printf("Protocol adress length: %d ",pln);
		switch(pln)
		{
			case 4:
				printf("IPv4");
				break;
			case 16:
				printf("IPv6");
				break;
			//TODO default
		}
		printf("\n");
		printLevelLayer();

	}

	void* addrTmp = entete + sizeof(struct arphdr);

	if(verbose >= 2)
	{
		printf("Sender Hardware Address: ");
		if(hrd == ARPHRD_ETHER && hln == 6)
		{
			printEthAddr((u_int8_t*)addrTmp);
		}
		else
		{
			printf("Adresse physique pas ethernet");
		}
		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}


		if(verbose == 3)
		{
			printLevelLayer();
		}
	}

	addrTmp += hln;
	if(verbose >= 2)
	{
		printf("Sender Internet Address: ");
		if(pro == 0x800)
		{
			switch(pln)
			{
				case 4:
					printIPv4Addr_u_int8((u_int8_t*)addrTmp);
					break;
				case 16:
					printIPv6Addr((u_int8_t*)addrTmp);
					break;
				//TODO default
			}
		}
		else
		{
			printf("Pas IP utilisé");
		}
		if(verbose == 3)
		{
			printf("\n");
			printLevelLayer();
		}
		else
		{
			printf("\t");
		}
	}
	addrTmp += pln;


	if(verbose >= 2)
	{
		printf("Target Hardware address: ");
		switch(op)
		{
			case ARPOP_REQUEST:
				printf("Requete, donc adresse de niveau 2 inconnu");
				break;
			case ARPOP_REPLY:
				if(hrd == ARPHRD_ETHER && hln == 6)
				{
					printEthAddr((u_int8_t*)addrTmp);
				}
				else
				{
					printf("Adresse physique pas ethernet");
				}		
				break;
			default:
				printf("Opcode inconnu");
		}
		if(verbose == 3)
		{
			printf("\n");
			printLevelLayer();
		}
		else
		{
			printf("\t");
		}
	}

	addrTmp += hln;


	printf("Target Internet Address: ");
	if(pro == 0x800)
	{
		switch(pln)
		{
			case 4:
				printIPv4Addr_u_int8((u_int8_t*)addrTmp);
				break;
			case 16:
				printIPv6Addr((u_int8_t*)addrTmp);
				break;
			//TODO default
		}
	}
	else
	{
		printf("Pas IP utilisé");
	}

	printf("\n");
}
