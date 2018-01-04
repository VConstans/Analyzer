#include "fct_IPv6.h"

void treatIPv6(void* entete)
{
	printf("IPV6\n");

	struct ip6_hdr* enteteIP = (struct ip6_hdr*)entete;

	u_int32_t ctl = ntohl(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_flow);

	u_int8_t version = (ctl & 0xF0000000) >> 28;
        u_int8_t classe = 0;
	classe = (ctl & 0xFF00000) >> 20;
        u_int32_t label = 0;
	label = (ctl & 0xFFFFF);

	if(version != 6)
	{
		printf("Erreur, Ethernet indique un paquet IPv6, mais il ne s'agit pas d'un paquet IPv6\n");
		exit(-1);
	}

        printf("Version: %d\n",version);
        printf("Classe: %x\n",classe);
        printf("Label: %x\n",label);

	u_int16_t len = ntohs(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_plen);

	printf("Longueur: %d\n",len);
	printf("Next header: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt);
	printf("Hop limit: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_hlim);

	printIPv6Addr(enteteIP->ip6_src.__in6_u.__u6_addr8);
	printIPv6Addr(enteteIP->ip6_dst.__in6_u.__u6_addr8);

	//TODO option
/*
	u_int8_t next_header = enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt;
	u_int16_t length = enteteIP->ip6_ctlun.ip6_un1.ip6_un1_plen;

	while(next_header != 0x6 && next_header != 0x11)
	{
		switch(next_header)
		{
			case 0:
				printf("Option Hop by Hop\n");
				
				break;
		}
	}

*/

	void* enteteNiv4 = entete + sizeof(struct ip6_hdr);

	switch(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt)
	{
		case 0x06:
			treatTCP(enteteNiv4,len);
			break;
		case 0x11:
			treatUDP(enteteNiv4);
			break;
		default:
			printf("Pas de niveau 4");
			break;
	}
}
