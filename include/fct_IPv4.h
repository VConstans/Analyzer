#ifndef __fct_IPv4_h__
#define __fct_IPv4_h__

#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "fct_UDP.h"
#include "fct_tcp.h"
#include "utile.h"


void treatIPv4(void* entete);

#endif
