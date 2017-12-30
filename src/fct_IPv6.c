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
        printf("Classe: %d\n",classe);
        printf("Label: %d\n",label);

	printf("Longueur: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_plen);
	printf("Next header: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_nxt);
	printf("Hop limit: %d\n",enteteIP->ip6_ctlun.ip6_un1.ip6_un1_hlim);

	printIPv6Addr(enteteIP->ip6_src.__in6_u.__u6_addr8);
	printIPv6Addr(enteteIP->ip6_dst.__in6_u.__u6_addr8);

}
