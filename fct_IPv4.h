#ifndef __fct_IPv4_h__
#define __fct_IPv4_h__

#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


void treatIPv4(struct iphdr* entete);

#endif
