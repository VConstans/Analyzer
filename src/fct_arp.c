#include "fct_arp.h"

void treatARP(void* entete)
{
	struct arphdr* enteteARP = (struct arphdr*)entete;

	switch(enteteARP->ar_op)
	{
		case ARPOP_REQUEST:
			printf("ARP Request\n");
			break;
		case ARPOP_REPLY:
			printf("ARP Reply\n");
			break;
	}

	printf("Hardware type: %d\n ",enteteARP->ar_hrd);

	switch(enteteARP->ar_hrd)
	{
		case ARPHRD_ETHER:
			printf("Ethernet");
			break;

		//TODO autre cas
		//TODO default
	}
	printf("\n");


	printf("Protocol type: %d ",enteteARP->ar_pro);
	switch(enteteARP->ar_pro)
	{
		case 0x800:
			printf("IP");
			break;
		//TODO default
	}
	printf("\n");

	printf("Hardware length: %d",enteteARP->ar_hln);
	switch(enteteARP->ar_hln)
	{
		case 6:
			printf("Ethernet");
			break;

		//TODO autre cas
		//TODO default
	}
	printf("\n");


	printf("Protocol adress length: %d ",enteteARP->ar_pln);
	switch(enteteARP->ar_pln)
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


	void* addrTmp = (void*)(enteteARP + sizeof(struct arphdr));


	printf("Sender Hardware Address: ");
	if(enteteAPR->ar_hrd == ARPHRD_ETHER && enteteARP->arhln == 6)
	{
		printEthAddr((u_int8_t*)addrTmp);
	}
	else
	{
		printf("Adresse physique pas ethernet\n");
	}

	addrTmp += enteteARP->ar_hln;


	if(enteteARP->ar_pro == 0x800)
	{
		switch(enteteARP->ar_pln)
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
		printf("Pas IP utilisé\n");
	}

	addrTmp += enteteARP->ar_pln;


	//TODO continuer
}
