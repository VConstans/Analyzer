#ifndef __fct_ethernet_h__
#define __fct_ethernet_h__

#include <stdio.h>
#include <stdlib.h>

#include <net/ethernet.h>
#include <netinet/ip.h>
#include "fct_IPv4.h"


void treatEthernet(void* entete);


#endif
