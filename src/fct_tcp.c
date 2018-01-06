#include "fct_tcp.h"

void treatTCP(void* entete,int len)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 2;

	printLevelLayer();
	printf("TCP:\n");

	struct tcphdr* enteteTCP = (struct tcphdr*) entete;

	u_int16_t source = ntohs(enteteTCP->source);
	u_int16_t destination = ntohs(enteteTCP->dest);
	u_int32_t seq = ntohl(enteteTCP->seq);
	u_int32_t ack_seq = ntohl(enteteTCP->ack_seq);

	printLevelLayer();
	printf("Port Source %d\n",source);
	printLevelLayer();
	printf("Port destination %d\n",destination);
	printLevelLayer();
	printf("Numéro de séquence %u\n",seq);	//TODO mauvais numéro
	printLevelLayer();
	printf("Numéro d'ack %u\n",ack_seq);		//TODO mauvais numéro



	int hdrLen = enteteTCP->doff;
	printLevelLayer();
	printf("Data offset %d\n",hdrLen);


	printLevelLayer();
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

	printLevelLayer();
	printf("Window %d\n",ntohs(enteteTCP->window));

	printLevelLayer();
	printf("Checksum %x\n",ntohs(enteteTCP->check)); 

	printLevelLayer();
	printf("Urgent pointer %d\n",ntohs(enteteTCP->urg_ptr)); 	//XXX quel boutisme?


	if(hdrLen > 5)
	{
		//TODO traiter options
	}

	//TODO traiter bourrage


	void* enteteNiv7 = entete +4*hdrLen;

	len -= 4*hdrLen;

	if(len > 0 /*&& enteteTCP->psh*/)
		{

		if(source == 80 || destination == 80)
		{
			treatHTTP(enteteNiv7,len);
		}

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
