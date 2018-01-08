#include "analyzer.h"

int levelPrinting = 0;
int verbose = 1;

void got_packets(u_char* args,const struct pcap_pkthdr* header, const u_char* packet)
{
	if(args){}	//UNUSED
	if(header){}	//UNUSED

	struct ether_header* enteteEthernet = (struct ether_header*)packet; 

	treatEthernet(enteteEthernet);
}

int main(int argc,char* argv[])
{
	char arg;
	char* nom_src = NULL;
	int src;

	while((arg = getopt(argc,argv,"i:o:v:")) != -1)
	{
		switch(arg)
		{
			case 'i':
				nom_src = optarg;
				src = INTERFACE;
				break;
			case 'o':
				nom_src = optarg;
				src = FICHIER;
				break;
			case 'v':
				verbose = atoi(optarg);
				break;
		}
	}


	char errbuf[PCAP_ERRBUF_SIZE];

	//TODO regarder si l'interface existe

	pcap_t* interface;
	switch(src)
	{
		case INTERFACE:
			interface = pcap_open_live(nom_src,1600,0,0,errbuf);
			break;
		case FICHIER:
			interface = pcap_open_offline(nom_src,errbuf);
			break;
		default:
			printf("Pas de source selectionne\n");
			exit(-1);
			break;
	}

	pcap_loop(interface,-1,*got_packets,NULL);

	//TODO carpturer SIGINT pour close

	return 0;
}
