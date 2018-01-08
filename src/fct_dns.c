#include "fct_dns.h"


void decodeClass(u_int16_t class)
{
	printLevelLayer();
	printf("Class: ");
	switch(class)
	{
		case 1:
			printf("(IN) Internet");
			break;
		default:
			printf("Unreconized Class");
			break;
	}
	printf("\n");
}

void decodeType(u_int16_t type)
{
	printLevelLayer();
	printf("Type: ");
	switch(type)
	{
		case 1:
			printf("A");
			break;
		case 2:
			printf("NS");
			break;
		case 5:
			printf("CNAME");
			break;
		case 6:
			printf("SOA");
			break;
		case 12:
			printf("PTR");
			break;
		case 15:
			printf("MX");
			break;
		case 28:
			printf("AAAA");
			break;
		default:
			printf("Unreconized Type");
			break;
	}
	printf("\n");
}


u_int8_t* printLabel(u_int8_t* name, u_int8_t* entete)
{
	while(*name != 0x0)
	{
		if(((*name & 0xc0) >> 6) == 0x3)
		{
			u_int16_t offset = (ntohs(*(u_int16_t*)(name)) & 0x3fff);
			printLabel(entete + offset,entete);
			name ++;
			break;
		}
		else
		{
			u_int8_t length = *name;
			name++;
			u_int8_t i;
			for(i=0;i<length;i++)
			{
				printf("%c",*name);
				name++;
			}
			if(*name != 0x0)
			{
				printf(".");
			}
		}
	}
	return ++name;
}



u_int8_t* decodeAnswer(u_int8_t* curseur,u_int8_t* entete)
{
	printLevelLayer();
	u_int8_t* finName = printLabel(curseur,entete);
	printf("\n");
	struct dns_answer* answer = (struct dns_answer*)finName;

	u_int16_t class = ntohs(answer->aclass);
	u_int16_t type = ntohs(answer->atype);
	u_int32_t ttl = ntohl(answer->attl);
	u_int16_t len = ntohs(answer->alen);

	decodeType(type);
	decodeClass(class);

	printLevelLayer();
	printf("TTL: %d\n",ttl);
	printLevelLayer();
	printf("Data length: %d\n",len);

	u_int8_t* answer_end = finName + 10 + len;

	if(class == 1)
	{
		printLevelLayer();
		u_int8_t* fin;
		switch(type)
		{
			case 1:
				if(len == 4)
				{
					printf("Adress: ");
					printIPv4Addr_u_int8(&answer->adata);
					printf("\n");
				}
				else
				{
					printf("Error, data format and length doesn't coherent\n");
				}
				break;
			case 2:
				printf("Name: ");
				printLabel(&answer->adata,entete);
				printf("\n");
				break;
			case 5:
				printf("Name: ");
				printLabel(&answer->adata,entete);
				printf("\n");
				break;
			case 6:
				printf("Primary NS: ");
				fin = printLabel(&answer->adata,entete);
				printf("\n");
				printf("Admin mailbox: ");
				fin = printLabel(fin,entete);
				printf("\n");

				u_int32_t* SOA_data = (u_int32_t*)fin;
				printf("Serial Number: %d\n",ntohl(SOA_data[0]));
				printf("Refresh Interval: %d\n",ntohl(SOA_data[1]));
				printf("Retry Interval: %d\n",ntohl(SOA_data[2]));
				printf("Expiration Limit: %d\n",ntohl(SOA_data[3]));
				printf("Minimum TTL: %d\n",ntohl(SOA_data[4]));
				
				break;
			case 12:
				printf("Name: ");
				printLabel(&answer->adata,entete);
				printf("\n");
				break;
			case 15:
				printf("Preference: %d",*((u_int16_t*)(&answer->adata)));
				printf("Mail Exchanger: ");
				printLabel(&(answer->adata) + 2,entete);
				printf("\n");
				break;
			case 28:
				if(len == 16)
				{
					printf("Adress: ");
					printIPv6Addr(&answer->adata);
					printf("\n");
				}
				else
				{
					printf("Error, data format and length doesn't coherent\n");
				}
				break;
			default:
				printf("Unreconized Type");
				break;
		}
	}

	return answer_end;
}


void treatDNS(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 3;

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("DNS:");
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}
	struct dns_header* enteteDNS = (struct dns_header*)entete;

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Identifier: %x\n",ntohs(enteteDNS->tid));
	}

	u_int16_t flags = ntohs(enteteDNS->flags);
	if(verbose >= 2)
	{
		if(verbose == 3)
		{
			printLevelLayer();
		}
		printf("Flags: %x ",flags);
	}

	if((flags & 0x8000) >> 15)
	{
		printf("Response, ");
	}
	else
	{
		printf("Query, ");
	}

	if(verbose >= 2)
	{
		switch((flags & 0x7800) >> 11)
		{
			case 0:
				printf("Standard Query, ");
				break;
			case 1:
				printf("Inverse Query, ");
				break;
			case 2:
				printf("Server Status Request, ");
				break;
			case 4:
				printf("Notify, ");
				break;
			case 5:
				printf("Update, ");
				break;
			default:
				printf("Unreconized dns opcode, ");
				break;
		}

		if((flags & 0x400) >> 10)	{printf("Authoritative Answer, ");}
		if((flags & 0x200) >> 9)	{printf("Truncate message, ");}
		if((flags & 0x100) >> 8)	{printf("Recursion Desired, ");}
		if((flags & 0x80) >> 7)		{printf("Recursion Available, ");}

		switch(flags & 0xf)
		{
			case 0:
				printf("No error");
				break;
			case 1:
				printf("Format Error");
				break;
			case 2:
				printf("Server Failure");
				break;
			case 3:
				printf("Name Error");
				break;
			case 4:
				printf("Not Implemented");
				break;
			case 5:
				printf("Refused");
				break;
			default:
				printf("Unreconized Reply Code");
		}

		if(verbose == 3)
		{
			printf("\n");
		}
		else
		{
			printf("\t");
		}
	}

	u_int16_t nquestion = ntohs(enteteDNS->nqueries);
	u_int16_t nanswer = ntohs(enteteDNS->nanswers);
	u_int16_t nauth = ntohs(enteteDNS->nauth);
	u_int16_t nother = ntohs(enteteDNS->nother);

	if(verbose == 3)
	{
		printLevelLayer();
		printf("Questions: %d\n",nquestion);
		printLevelLayer();
		printf("Answer RR: %d\n",nanswer);
		printLevelLayer();
		printf("Authority RR: %d\n",nauth);
		printLevelLayer();
		printf("Additional RR: %d\n",nother);

		u_int8_t* curseur = &(enteteDNS->data);

		int i;
		if(nquestion > 0)
		{
			printLevelLayer();
			printf("Queries\n");
		}

		for(i=0;i<nquestion;i++)
		{
			printLevelLayer();
			u_int8_t* finName = printLabel(curseur,entete);
			printf("\n");
			struct dns_querie* querie = (struct dns_querie*)finName;

			decodeType(ntohs(querie->qtype));
			decodeClass(ntohs(querie->qclass));

			curseur = finName + 4;
		}
		printf("\n");

		if(nanswer > 0)
		{
			printLevelLayer();
			printf("Answer\n");
		}
		for(i=0;i<nanswer;i++)
		{
			curseur = decodeAnswer(curseur,entete);
		}
		printf("\n");

		if(nauth > 0)
		{
			printLevelLayer();
			printf("Authtority Record\n");
		}
		for(i=0;i<nauth;i++)
		{
			curseur = decodeAnswer(curseur,entete);
		}
		printf("\n");

		if(nother > 0)
		{
			printLevelLayer();
			printf("Additional Record\n");
		}
		for(i=0;i<nother;i++)
		{
			curseur = decodeAnswer(curseur,entete);
		}
		printf("\n");
	}
}
