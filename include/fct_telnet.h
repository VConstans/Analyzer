#ifndef __FCT_TELNET_H__
#define __FCT_TELNET_H__

#define IAC 255
#define NOP 241
#define DM 242
#define IP 244
#define AO 245
#define AYT 246
#define EC 247
#define EL 248
#define GA 249
#define SB 250
#define SE 240
#define WILL 251
#define WONT 252
#define DO 253
#define DONT 254
#define ECHO 0x1
#define SGA 0x3
#define TT 0x18
#define WS 0x1f
#define TS 0x20
#define LM 0x22
#define EV 0x24
#define NEV 0x27

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>


void treatTelnet(void*,int);

#endif
