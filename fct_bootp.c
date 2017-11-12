#include "fct_bootp.h"
#include "utile.h"

void treatBootp(void* entete)
{
	struct bootp* enteteB = (struct bootp*)entete;

	printf("BOOTP\n");

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

	printf("htype %d\n",enteteB->bp_htype);
	printf("hlen %d\n",enteteB->bp_hlen);
	printf("hops %d\n",enteteB->bp_hops);
	printf("xid %x\n",ntohl(enteteB->bp_xid));
	printf("sec %d\n",enteteB->bp_secs);
	printf("flags %x\n",enteteB->bp_flags);

	//TODO printf nom addr
	printIPv4Addr((u_int32_t)(enteteB->bp_ciaddr.s_addr));
	printIPv4Addr((u_int32_t)(enteteB->bp_yiaddr.s_addr));
	printIPv4Addr((u_int32_t)(enteteB->bp_siaddr.s_addr));
	printIPv4Addr((u_int32_t)(enteteB->bp_giaddr.s_addr));

	//Si les adresses physique sont de type ethernet
	if(enteteB->bp_hlen == 6)
	{
		printf("Adresse physique du client: ");
		printEthAddr(enteteB->bp_chaddr);
	}

	//TODO sname
	//TODO file


	printf("vend ");
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

	switch(type)
	{
		case TAG_DHCP_MESSAGE:
			//XXX verifier si len ==1?
			switch(value[0])
			{
				case DHCPDISCOVER:
					break;
				case DHCPOFFER:
					break;
				case DHCPREQUEST:
					break;
				case DHCPDECLINE:
					break;
				case DHCPACK:
					break;
				case DHCPNAK:
					break;
				case DHCPRELEASE:
					break;
				case DHCPINFORM:
					break;
			}
			break;
		case TAG_END:
			return;
	}

	decodeDHCPOption(ptrOption+2+len);
}
