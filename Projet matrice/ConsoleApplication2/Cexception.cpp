#include "stdafx.h"
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
Cexception::Cexception(unsigned int exception)
{
	uiEXCValeur=exception;
}

/**
* Destructeur
* Ne fait rien
*/
Cexception::~Cexception(void)
{
}

/**
* Changer la valeur de l'exception
* @param: unsigned int (exception)
*/
void Cexception::EXCModifierException(unsigned int exception)
{
	uiEXCValeur=exception;
}

/**
* Lire l'exception
* @return: unsigned int (la valeur de l'exception)
* donne la valeur de l'exception lev�e 
*/
unsigned int Cexception::eEXCLireException()
{
	return uiEXCValeur;
}
