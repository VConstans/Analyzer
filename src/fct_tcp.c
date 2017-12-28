#include "fct_tcp.h"

void treatTCP(void* entete,int len)
{
	struct tcphdr* enteteTCP = (struct tcphdr*) entete;

	printf("Port Source %d\n",ntohs(enteteTCP->source));
	printf("Port destination %d\n",ntohs(enteteTCP->dest));
	printf("Numéro de séquence %u\n",enteteTCP->seq);	//TODO mauvais numéro
	printf("Numéro d'ack %u\n",enteteTCP->ack_seq);		//TODO mauvais numéro

	int hdrLen = enteteTCP->doff;
	printf("Data offset %d\n",hdrLen);


	printf("Flags: ");
	if(enteteTCP->ack)
	{
		printf("ACK ");
	}
	if(enteteTCP->urg)
	{
		printf("URG ");
	}
	if(enteteTCP->syn)
	{
		printf("SYN ");
	}
	if(enteteTCP->fin)
	{
		printf("FIN ");
	}
	if(enteteTCP->psh)
	{
		printf("PSH ");
	}
	if(enteteTCP->rst)
	{
		printf("RST ");
	}
	//TODO autre flags
	printf("\n");

	printf("Window %d\n",ntohs(enteteTCP->window));

	printf("Checksum %x\n",ntohs(enteteTCP->check)); 
	printf("Urgent pointer %d\n",ntohs(enteteTCP->urg_ptr)); 	//XXX quel boutisme?


	if(hdrLen > 5)
	{
		//TODO traiter options
	}


	void* enteteNiv7 = entete +4*hdrLen;

	if(enteteTCP->source == 80 || enteteTCP->dest == 80)
	{
		treateHTTP(enteteNiv7,len-4*hdrLen);
	}

	//TODO treat https?
}
