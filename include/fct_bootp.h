#ifndef __FCT_BOOTP_H__
#define __FCT_BOOTP_H__

#include "bootp.h"
#include <stdio.h>
#include <stdlib.h>
#include "utile.h"

void treatBootp(void*);
void decodeDHCPOption(u_int8_t*);
void decodeParameterRequestList(u_int8_t);

#endif
