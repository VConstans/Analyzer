#include "analyzer.h"

int levelPrinting = 0;

void got_packets(u_char* args,const struct pcap_pkthdr* header, const u_char* packet)
{
	struct ether_header* enteteEthernet = (struct ether_header*)packet; 

	treatEthernet(enteteEthernet);
}

int main(int argc,char* argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];

	char* listDev = NULL;

	listDev=pcap_lookupdev(errbuf);
	if(listDev == NULL)
	{
		perror("Erreur findalldevs");
	}

	printf("%s",argv[1]);
	pcap_t* interface = pcap_open_live(argv[1],1600,0,0,errbuf);

	pcap_loop(interface,-1,*got_packets,NULL);

	return 0;
}
