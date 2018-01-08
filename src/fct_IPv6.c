#include "fct_IPv6.h"

void treatIPv6(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 1;

	if(verbose >= 2)
	{
		printLevelLayer();
		printf("IPv6: ");
	}

	struct ip6_hdr* enteteIP = (struct ip6_hdr*)entete;

	u_int32_t ctl = ntohl(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_flow);

	u_int8_t version = (ctl & 0xF0000000) >> 28;
        u_int8_t classe = 0;
	classe = (ctl & 0xFF00000) >> 20;
        u_int32_t label = 0;
	label = (ctl & 0xFFFFF);

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Version: %d\n",version);
		printLevelLayer();
		printf("Classe: %x\n",classe);
		printLevelLayer();
		printf("Label: %x\n",label);
		printLevelLayer();
	}


	u_int16_t len = ntohs(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_plen);

	if(verbose >= 2)
	{
		printf("Longueur: %d\t",len);

		if(verbose == 3)
		{
			printf("\n");
		}
	}

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Next header: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt);

		printLevelLayer();
	}

	if(verbose >= 2)
	{
		printf("Hop limit: %d\t",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_hlim);

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

	printf("Source Address: ");
	printIPv6Addr(enteteIP->ip6_src.__in6_u.__u6_addr8);

	if(verbose == 3)
	{
		printf("\n");
		printLevelLayer();
	}
	else
	{
		printf("\t");
	}

	printf("Destination Address: ");
	printIPv6Addr(enteteIP->ip6_dst.__in6_u.__u6_addr8);
	printf("\t");


	void* enteteNiv4 = entete + sizeof(struct ip6_hdr);

	if(verbose >=2)
	{
		printf("\n");
	}

	switch(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt)
	{
		case 0x06:
			treatTCP(enteteNiv4,len);
			break;
		case 0x11:
			treatUDP(enteteNiv4);
			break;
		default:
			if(verbose ==3)
			{
				printLevelLayer();
			}
			printf("No transport layer");
			break;
	}
}
