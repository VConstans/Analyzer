#ifndef __FCT_TCP_H__
#define __FCT_TCP_H__

#include <stdio.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "fct_http.h"
#include "fct_smtp.h"
#include "fct_ftp.h"
#include "fct_telnet.h"
#include "fct_pop.h"
#include "fct_imap.h"


void treatTCP(void*,int);


#endif
