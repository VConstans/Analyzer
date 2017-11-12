#ifndef __UTILE_H__
#define __UTILE_H__

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/ethernet.h>


void printIPv4Addr(u_int32_t addr);
void printEthAddr(u_int8_t addr[]);


#endif
