#ifndef __FCT_BOOTP_H__
#define __FCT_BOOTP_H__

#include "netinet/bootp.h"
#include <stdio.h>
#include <stdlib.h>

void treatBootp(void* entete);
void decodeDHCPOption(u_int8_t* ptrOption);

#endif
