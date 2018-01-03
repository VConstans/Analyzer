#ifndef __FCT_DNS_H__
#define __FCT_DNS_H__

#include <stdlib.h>
#include <stdio.h>
#include "utile.h"

struct dns_header
{
	u_int16_t tid;
	u_int16_t flags;
	u_int16_t nqueries;
	u_int16_t nanswers;
	u_int16_t nauth;
	u_int16_t nother;
	u_int8_t data;
};

struct dns_querie
{
	/* Name */
	u_int16_t qtype;
	u_int16_t qclass;
};

struct dns_answer
{
	/* Name */
	u_int16_t atype;
	u_int16_t aclass;
	u_int32_t attl;
	u_int16_t alen;
	u_int8_t adata;
};


void decodeClass(u_int16_t);
void decodeType(u_int16_t);
u_int8_t* printLabel(u_int8_t*, u_int8_t*);
u_int8_t* decodeAnswer(u_int8_t*,u_int8_t*);
void treatDNS(void*);

#endif
