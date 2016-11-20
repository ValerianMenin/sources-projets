#include "stdafx.h"
#include "Cexception.h"

/**
* Constructeur par défaut
* Ne fais rien
*/
Cexception::Cexception(void)
{
}

/**
* Constructeur prenant la valeur de l'exception
* @param: unsigned int (valeur exception)
* @Entraine: Créer une exception avec la valeur donnée
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
* donne la valeur de l'exception levée 
*/
unsigned int Cexception::eEXCLireException()
{
	return uiEXCValeur;
}
