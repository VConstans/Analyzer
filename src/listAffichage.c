#include "listAffichage.h"

struct listAffichage* getAffichage(struct listAffichage* listAffichage,u_int16_t port,int sens)
{
	while(listAffichage != NULL)
	{
		if(listAffichage->port == port && listAffichage->sens == sens)
		{
			return listAffichage;
		}
		listAffichage = listAffichage->suivant;
	}
	return NULL;
}


struct listAffichage* setAffichage(struct listAffichage* listAffichage,u_int16_t port,int sens ,int affichage)
{
	if(listAffichage == NULL)
	{
		struct listAffichage* newAffichage = malloc(sizeof(struct listAffichage));
		newAffichage->port = port;
		newAffichage->sens = sens;
		newAffichage->affichage = affichage;

		return newAffichage;
	}

	struct listAffichage* curseur = listAffichage;
	while(curseur->suivant != NULL)
	{
		if(curseur->port == port && curseur->sens == sens)
		{
			curseur->affichage = affichage;
			return  listAffichage;
		}
		curseur = curseur->suivant;
	}

	struct listAffichage* newAffichage = malloc(sizeof(struct listAffichage));
	newAffichage->port = port;
	newAffichage->sens = sens;
	newAffichage->affichage = affichage;

	return listAffichage;
}
