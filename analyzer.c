#include <stdlib.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <pcap.h>


void got_packets(u_char* args,const struct pcap_pkthdr* header, const u_char* packet)
{
	struct ether_header* enteteEthernet = (struct ether_header*)packet; 

	treatEthernet(enteteEthernet);
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

	pcap_t* interface = pcap_open_live("wlan1",1600,0,0,errbuf);

	pcap_loop(interface,5,*got_packets,NULL);

	return 0;
}
