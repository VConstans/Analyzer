#ifndef __FCT_TELNET_H__
#define __FCT_TELNET_H__

#define IAC 255		//Interpreter as command
#define NOP 241		//No Operation
#define DM 242		//Data Mark
#define IP 244		//Interrupt Process
#define AO 245		//Abort output
#define AYT 246		//Are you there
#define EC 247		//Erase character
#define EL 248		//Erase Line
#define GA 249		//Go Ahead
#define SB 250		//Suboption
#define SE 240		//Suboption end
#define WILL 251	//Will
#define WONT 252	//Won't
#define DO 253		//DO
#define DONT 254	//Don't
#define ECHO 0x1	//Echo
#define SGA 0x3		//Suppress Go Ahead
#define TT 0x18		//Terminal Type
#define WS 0x1f		//Window Size
#define TS 0x20		//Terminal Speed
#define LM 0x22		//Line Mode
#define EV 0x24		//Environment Variable
#define NEV 0x27	//New Environment Variable
#define XDL 0x23	//X Display Location

#define SEND 0x1	//SENS
#define IS 0x0		//IS

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include "utile.h"


void treatTelnet(void*,int);

#endif
