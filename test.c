#include <stdlib.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <pcap.h>


void got_packets(u_char* args,const struct pcap_pkthdr* header, const u_char* packet)
{
	struct ether_header* enteteEthernet = (struct ether_header*)packet; 

	printf("Adresse dest\t");
	int i=0;

	for(i=0; i<ETH_ALEN ; i++)
	{
		printf("%x:",enteteEthernet->ether_dhost[i]);
	}

	printf("\tAdresse src\t");
	for(i=0; i<ETH_ALEN ; i++)
	{
		printf("%x:",enteteEthernet->ether_shost[i]);
	}


	printf("\t");
	printf("%x\n",enteteEthernet->ether_type);

	if(enteteEthernet->ether_type == 0x0008 || enteteEthernet->ether_type == 0xdd86)
	{
		struct iphdr* enteteIP = packet+sizeof(struct ether_header);
		printf("=> version %d\n",enteteIP->version);
	}

}

int main()
{
	char errbuf[PCAP_ERRBUF_SIZE];

	char* listDev = NULL;

	listDev=pcap_lookupdev(errbuf);
	if(listDev == NULL)
	{
		perror("Erreur findalldevs");
	}

	pcap_t* interface = pcap_open_live("eth1",1600,0,0,errbuf);

	pcap_loop(interface,5,*got_packets,NULL);

	return 0;
}
