#ifndef __FCT_DNS_H__
#define __FCT_DNS_H__

#include <stdlib.h>
#include <stdio.h>
#include "utile.h"

struct dns_header
{
	u_int16_t tid;		//Identifier
	u_int16_t flags;	//Flags
	u_int16_t nqueries;	//Number of queries
	u_int16_t nanswers;	//Number of Answers
	u_int16_t nauth;	//Number of Authority Answers
	u_int16_t nother;	//Number of Additional Answers
	u_int8_t data;
};

struct dns_querie
{
	/* Name */
	u_int16_t qtype;	//Querie Type
	u_int16_t qclass;	//Querie Class
};

struct dns_answer
{
	/* Name */
	u_int16_t atype;	//Answer type
	u_int16_t aclass;	//Answer class
	u_int32_t attl;		//Answer TTL
	u_int16_t alen;		//Answer Length
	u_int8_t adata;		//Answer Data
};


void decodeClass(u_int16_t);
void decodeType(u_int16_t);
u_int8_t* printLabel(u_int8_t*, u_int8_t*);
u_int8_t* decodeAnswer(u_int8_t*,u_int8_t*);
void treatDNS(void*);

#endif
