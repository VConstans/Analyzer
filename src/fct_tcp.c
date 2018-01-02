#include "fct_tcp.h"

void treatTCP(void* entete,int len)
{
	struct tcphdr* enteteTCP = (struct tcphdr*) entete;

	u_int16_t source = ntohs(enteteTCP->source);
	u_int16_t destination = ntohs(enteteTCP->dest);

	printf("Port Source %d\n",source);
	printf("Port destination %d\n",destination);
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

	//TODO traiter bourrage


	void* enteteNiv7 = entete +4*hdrLen;

	len -= 4*hdrLen;

	if(len != 0)
		{

		if(source == 80 || destination == 80)
		{
			treatHTTP(enteteNiv7,len);
		}


		//TODO treat https?

		if(source == 25 || destination == 25)
		{
			treatSMTP(enteteNiv7,len);
		}

		if(source == 21 ||/* source == 20 ||*/ destination == 21 /*|| destination == 20*/)
		{
			treatFTP(enteteNiv7,len);
		}

		if(source == 23 || destination == 23)
		{
			treatTelnet(enteteNiv7,len);
		}
	}
}
