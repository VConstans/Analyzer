#include "fct_telnet.h"

void treatTelnet(void* entete,int len)
{
	printf("Telnet\n");

	u_int8_t* message = (u_int8_t*)entete;

	int i;
	for(i=0;i<len;i++)
	{
		if(message[i] == IAC)
		{
			i++;
			switch (message[i])
			{
				case NOP:
					printf("NOP (no operation)\n");
					break;
;				case DM:
					printf("Data Mark\n");
					break;
				case IP:
					printf("Interrupt Process\n");
					break;
				case AO:
					printf("Abort Output\n");
					break;
				case AYT:
					printf("Are You There\n");
					break;
				case EC:
					printf("Erase Character\n");
					break;
				case EL:
					printf("Erase Line\n");
					break;
				case GA:
					printf("Go Ahead\n");
					break;
				case SB:
					printf("Suboption ");
					i++;
					while(message[i] != SE)
					{
						switch(message[i])
						{
							case TT:
								//TODO
								break;
							case WS:
								i++;
								printf("Terminal Size: ");
								printf("Width: %d ",ntohs(*((u_int16_t*)(message+i))));
								i+=2;
								printf("Width: %d ",ntohs(*((u_int16_t*)(message+i))));
								//TODO
						}
						i++;
					}
					printf("Suboption End\n");
					break;
				case WILL:
					printf("WILL ");
					break;
				case WONT:
					printf("WON'T ");
					break;
				case DO:
					printf("DO ");
					break;
				case DONT:
					printf("DON'T ");
					break;
				
				default:
					printf("Option non reconnu\n");
			}

			if(message[i] == WILL || message[i] == WONT || message[i] == DO || message[i] == DONT)
			{
				i++;
				switch(message[i])
				{
					case ECHO:
						printf("Echo\n");
						break;
					case SGA:
						printf("Suppress Go Ahead\n");
						break;
					case TT:
						printf("Terminal Type\n");
						break;
					case WS:
						printf("Window Size\n");
						break;
					case TS:
						printf("Terminal Speed\n");
						break;
					case LM:
						printf("Line Mode\n");
						break;
					case EV:
						printf("Environment Variables\n");
						break;
					case NEV:
						printf("New Environment Variables\n");
						break;
					default:
						printf("Option non reconu\n");
						break;
				}
			}
		}
		else
		{
			printf("%c",message[i]);
		}
	}
}