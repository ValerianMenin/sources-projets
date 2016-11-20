
#include "Cexception.h"

/**
*	Entree :
*		@param pcexception : une chaine de caracteres dans lequel est ecrit un message
*		@param bEXCendExecution : un booleen optionnel qui indique si c'est une erreur pour "true" et ou un warning pour "false" (de base, c'est une erreur)
*	Necessite : -
*	Sortie : -
*	Entraine : creation d'une erreur
*/
Cexception::Cexception(char* cexception, bool bEXCendExecutionParam)
{
	this->bEXCendExecution = bEXCendExecutionParam;
	int eIndex = 0;
	while (cexception[eIndex] != '\0')
	{
		pcEXCvalue[eIndex] = cexception[eIndex];
		eIndex++;
	}
	pcEXCvalue[eIndex] = '\0';
}


/**
*	Entree : une reference sur une erreur
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage de l'exception et fin de programme si c'est une erreur
*/
std::ostream &operator<<(std::ostream & OSTflux, Cexception & EXCparam)
{
	int eIndex = 0;
	while (EXCparam.EXCgetpcEXCvalue()[eIndex] != '\0')
	{
		std::cerr << EXCparam.EXCgetpcEXCvalue()[eIndex];
		eIndex++;
	}
	std::cerr << std::endl;
	if (EXCparam.EXCgetEndOfExecution() == true)// si c'est une erreur, on arrete le programme (sinon c'est un warning et le traitement continue)
		exit(1);
	return std::cerr;
}
