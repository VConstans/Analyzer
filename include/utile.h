#ifndef __UTILE_H__
#define __UTILE_H__

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/ethernet.h>


void printIPv4Addr(u_int32_t);
void printIPv6Addr(uint8_t*);
void printEthAddr(u_int8_t*);
void printHexToAscii_len(int, u_int8_t*);
void printIPv4Addr_u_int8(u_int8_t*);
void printLevelLayer();
void printHexToAscii(u_int8_t);
void printfAlign(char*);


#endif
