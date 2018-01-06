#include "fct_bootp.h"
#include "utile.h"

void treatBootp(void* entete)
{
	extern int levelPrinting;
	levelPrinting = 3;

	printLevelLayer();
	printf("BOOTP\n");

	struct bootp* enteteB = (struct bootp*)entete;


	printLevelLayer();
	switch(enteteB->bp_op)
	{
		case 1:
			printf("Request\n");
			break;
		case 2:
			printf("Response\n");
			break;
		default:
			printf("Type de message bootp inconnu\n");
	}

	printLevelLayer();
	printf("htype %d\n",enteteB->bp_htype);
	printLevelLayer();
	printf("hlen %d\n",enteteB->bp_hlen);
	printLevelLayer();
	printf("hops %d\n",enteteB->bp_hops);
	printLevelLayer();
	printf("xid %x\n",ntohl(enteteB->bp_xid));
	printLevelLayer();
	printf("sec %d\n",enteteB->bp_secs);
	printLevelLayer();
	printf("flags %x\n",enteteB->bp_flags);

	//TODO printf nom addr
	printLevelLayer();
	printIPv4Addr((u_int32_t)(enteteB->bp_ciaddr.s_addr));
	printLevelLayer();
	printIPv4Addr((u_int32_t)(enteteB->bp_yiaddr.s_addr));
	printLevelLayer();
	printIPv4Addr((u_int32_t)(enteteB->bp_siaddr.s_addr));
	printLevelLayer();
	printIPv4Addr((u_int32_t)(enteteB->bp_giaddr.s_addr));

	//Si les adresses physique sont de type ethernet
	if(enteteB->bp_hlen == 6)
	{
		printLevelLayer();
		printf("Adresse physique du client: ");
		printEthAddr(enteteB->bp_chaddr);
	}

	//TODO sname
	//TODO file


	printLevelLayer();
	printf("Vendor: ");
	if(ntohl(*((u_int32_t*)(enteteB->bp_vend))) == 0x63825363)	//XXX magic cookie dans define
	{
		printf("Magic cookie\n");
		decodeDHCPOption(enteteB->bp_vend+4);
	}
	//else	TODO
}


void decodeDHCPOption(u_int8_t* ptrOption)
{
	u_int8_t type = ptrOption[0];
	u_int8_t len = ptrOption[1];
	u_int8_t* value = ptrOption + 2;


	int nb_param;
	int i;

	switch(type)
	{
		case TAG_DHCP_MESSAGE:
			//XXX verifier si len ==1?
			switch(value[0])
			{
				case DHCPDISCOVER:
					printf("DHCP DISCOVER\n");
					break;
				case DHCPOFFER:
					printf("DHCP OFFER\n");
					break;
				case DHCPREQUEST:
					printf("DHCP REQUEST\n");
					break;
				case DHCPDECLINE:
					printf("DHCP DECLINE\n");
					break;
				case DHCPACK:
					printf("DHCP ACK\n");
					break;
				case DHCPNAK:
					printf("DHCP NACK\n");
					break;
				case DHCPRELEASE:
					printf("DHCP RELEASE\n");
					break;
				case DHCPINFORM:
					printf("DHCP INFORM\n");
					break;
			}
			break;

		case TAG_SUBNET_MASK:
			//XXX verifier que le taille des masques est cohérente par rapport au taille donnée dans d'autre champs
			printf("Subnet mask: ");
			printEthAddr(value);
			break;

		case TAG_TIME_OFFSET:
			//TODO 
			break;

		case TAG_GATEWAY:
			//XXX tester quelle type d'adresse IP s'est
			//TODO verifier taille
			printf("Gateway: ");
			printIPv4Addr_u_int8(value);
			break;

		case TAG_DOMAIN_SERVER:
			nb_param = len/4;
			//XXX tester si le nb de dns est un nombre entier
			u_int8_t* curseur = value;

			printf("Domain servers: ");
			for(i=0;i<nb_param;i++)
			{
				//XXX tester quelle type d'adresse IP s'est
				//TODO verifier taille
				printIPv4Addr_u_int8(curseur);

				curseur = curseur + 4;
			}
			break;

		case TAG_HOSTNAME:
			printf("Hostname: ");
			printHexToAscii_len(len,value);
			printf("\n");
			break;

		case TAG_DOMAINNAME:
			printf("Domain name: ");
			printHexToAscii_len(len,value);
			printf("\n");
			break;

		case TAG_BROAD_ADDR:
			printf("Broadcast adress: ");
			printIPv4Addr_u_int8(value);
			break;

		//TODO case netbios 44 et 47


		case TAG_REQUESTED_IP:
			printf("Requested IP adress: ");
			printIPv4Addr_u_int8(value);
			break;

		case TAG_IP_LEASE:
			printf("Lease time: ");
			//TODO
			printf("\n");
			break;

		case TAG_SERVER_ID:
			printf("Server identifier: ");
			//TODO verifier taille adresse
			printIPv4Addr_u_int8(value);
			break;

		case TAG_PARM_REQUEST:
			nb_param = len;

			printf("Parameter request: ");
			for(i=0;i<nb_param;i++)
			{
				decodeParameterRequestList(value[i]);
			}
			printf("\n");
			break;

		case TAG_CLIENT_ID:
			if(value[0] == 1)	
			{
				if(len == 7)
				{
					printf("Client identifier: ");
					printEthAddr(&value[1]);
				}
				else
				{
					printf("Erreur, adresse malformé\n");
				}
			}
			else	
			{
				printf("Erreur, adresse de niveau 2 non ethernet\n");
			}
			break;

		case TAG_END:
			return;
	}

	decodeDHCPOption(ptrOption+2+len);
}


void decodeParameterRequestList(u_int8_t param)
{
	switch(param)
	{
		case TAG_SUBNET_MASK:
			printf("Subnet mask");
			break;

		case TAG_TIME_OFFSET:
			printf("Time offset");
			break;

		case TAG_GATEWAY:
			printf("Gateway");
			break;

		case TAG_DOMAIN_SERVER:
			printf("Domain server");
			break;

		case TAG_HOSTNAME:
			printf("Hostname");
			break;

		case TAG_DOMAINNAME:
			printf("Domain name");
			break;

		case TAG_BROAD_ADDR:
			printf("Broadcast adress");
			break;

		case TAG_NETBIOS_NS:
			printf("Netbios over TCP/IP Name Server");
			break;

		case TAG_NETBIOS_SCOPE:
			printf("Netbios over TCP/IP Scope");
			break;

		case TAG_REQUESTED_IP:
			printf("Requested IP adress");
			break;

		case TAG_IP_LEASE:
			printf("IP lease");
			break;

		case TAG_SERVER_ID:
			printf("Server identifier");
			break;

		case TAG_CLIENT_ID:
			printf("Client identifier");
			break;
	}

	printf(", ");
}
