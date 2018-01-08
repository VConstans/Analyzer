#include "fct_UDP.h"

/* Display information about UDP header */
void treatUDP(void* entete)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 2;

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("UDP");

	if(verbose == 1)
	{
		printf("\t");
	}
	else
	{
		printf(": ");
	}

	struct udphdr* enteteUDP = (struct udphdr*)entete;

	//Mise des informations dans le bon boutisme
	u_int16_t source = ntohs(enteteUDP->source);
	u_int16_t destination = ntohs(enteteUDP->dest);
	u_int16_t lg = ntohs(enteteUDP->len);
	u_int16_t check = ntohs(enteteUDP->check);

	if(verbose == 3)
	{
		printLevelLayer();
	}
	printf("Port source %d\t",source);
	if(verbose == 3)
	{
		printf("\n");
		printLevelLayer();
	}
	printf("Port destination %d\t",destination);
	if(verbose == 3)
	{
		printLevelLayer();
	}

	if(verbose >= 2)
	{
		printf("Longueur %d\t",lg);
		if(verbose == 3)
		{
			printf("\n");
			printLevelLayer();
		}
		printf("Checksum %x\t",check);
	}


	//Calcul du debut de l'entete de niveau applicatif
	void* enteteNiv7 = entete + sizeof(struct udphdr);

	if(verbose >= 2)
	{
		printf("\n");
	}

	/* Appelle de la fonction de traitement applicatif si il y a
	des données utiles à lui faire passer */
	if(lg > 8)
	{
		//BOOTP
		if(source == 67 || destination == 67 || source == 68 || destination == 68)
		{
			treatBootp(enteteNiv7);
		}

		//DNS
		if(source == 53 || destination == 53)
		{
			treatDNS(enteteNiv7);
		}
	}
}
