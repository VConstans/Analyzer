#include "fct_telnet.h"

void treatTelnet(void* entete,int len)
{
	extern int levelPrinting;
	extern int verbose;
	levelPrinting = 3;

	if( verbose == 3)
	{
		printLevelLayer();
	}
	printf("Telnet:");
	if(verbose == 3)
	{
		printf("\n");
	}
	else
	{
		printf("\t");
	}

	u_int8_t* message = (u_int8_t*)entete;


	if(verbose == 3)
	{

		int i;
		for(i=0;i<len;i++)
		{
			if(message[i] == IAC)
			{
					printLevelLayer();
					i++;
					switch (message[i])
					{
						case NOP:
							printf("NOP (no operation)\n");
							break;
						case DM:
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
							switch(message[i])
							{
								case TT:
									printf("Terminal Type: ");
									i++;
									switch(message[i])
									{
										case SEND:
											printf("SEND\n");
											break;
										case IS:
											i++;
											printf("IS ");
											while(message[i] != IAC && message[i+1] != SE)
											{
												printf("%c",message[i]);
												i++;
											}
											printf("\n");
											i--;
											break;
										default:
											printf("Erreur option Terminal Speed\n");
											break;
									}

									break;
								case WS:
									i++;
									printf("Terminal Size: ");
									printf("Width: %d ",ntohs(*((u_int16_t*)(message+i))));
									i+=2;
									printf("Height: %d\n",ntohs(*((u_int16_t*)(message+i))));
									break;
								case TS:
									printf("Terminal Speed: ");
									i++;
									switch(message[i])
									{
										case SEND:
											printf("SEND\n");
											break;
										case IS:
											i++;
											printf("Transmit speed: ");
											while(message[i] != ',')
											{
												printf("%c",message[i]);
												i++;
											}
											printf("\t");
											i++;
											printf("Receive speed: ");
											while(message[i] != IAC && message[i+1] != SE)
											{
												printf("%c",message[i]);
												i++;
											}
											printf("\n");
											i--;
											break;
										default:
											printf("Erreur option Terminal Speed\n");
											break;
									}
									break;

								case XDL:
									printf("X Display Location: ");
									i++;
									switch(message[i])
									{
										case SEND:
											printf("SEND\n");
											break;
										case IS:
											i++;
											printf("IS ");
											while(message[i] != IAC && message[i+1] != SE)
											{
												printf("%c",message[i]);
												i++;
											}
											printf("\n");
											i--;
											break;
										default:
											printf("Erreur option Terminal Speed\n");
											break;
									}

									break;
								default:
									printf("Unreconized Sub Option\n");
									break;
							}
							i++;
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
						case SE:
							printf("Suboption End\n");
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
							case XDL:
								printf("X Display Location\n");
								break;
							default:
								printf("Option non reconu\n");
								break;
						}
					}
				
			}
			else
			{
				printHexToAscii(message[i]);
			}
		}
	}
}
