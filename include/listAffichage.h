#ifndef __LIST_AFFICHAGE_H__
#define __LIST_AFFICHAGE_H__

#define SRC 0
#define DST 1

#include <stdlib.h>

struct listAffichage
{
	u_int16_t port;
	int sens;
	int affichage;
	struct listAffichage* suivant;
};

struct listAffichage* getAffichage(struct listAffichage*,u_int16_t,int);
struct listAffichage* setAffichage(struct listAffichage*,u_int16_t,int,int);

#endif
