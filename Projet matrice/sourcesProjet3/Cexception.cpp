#include "Cexception.h"

/**
* Constructeur par d�faut
* Ne fais rien
*/
Cexception::Cexception(void)
{
}

/**
* Constructeur prenant la valeur de l'exception
* @param: unsigned int (valeur exception)
* @Entraine: Cr�er une exception avec la valeur donn�e
*/
Cexception::Cexception(char* cexception)
{
	int eIndice = 0;
	while (cexception[eIndice] != '\0')
	{
		cEXCValeur[eIndice] = cexception[eIndice];
		eIndice++;
	}
	cEXCValeur[eIndice] = '\0';
}

/**
* Destructeur
* Ne fait rien
*/
Cexception::~Cexception(void)
{
}

std::ostream &operator<<(std::ostream & OSTflux, Cexception & EXCparam)
{
	int eIndice = 0;
	while (EXCparam.pcEXCLireException()[eIndice] != '\0')
	{
		cerr << EXCparam.pcEXCLireException()[eIndice];
		eIndice++;
	}
	return cerr;
}


