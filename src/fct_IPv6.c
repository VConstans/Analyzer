#include "fct_IPv6.h"

void treatIPv6(void* entete)
{
	printf("IPV6\n");

	struct ip6_hdr* enteteIP = (struct ip6_hdr*)entete;

	u_int32_t ctl = ntohl(enteteIP->ip6_ctlun.ip6_un1.ip6_un1_flow);

	

	printf("Version: %x\n",);
}
