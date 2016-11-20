
#include "CStringUtil.h"

/**
*	Entree : un pointeur sur une chaine de caracteres
*	Necessite : -
*	Sortie : un booleen
*		@return true si la chaine est un int
*		@return false si la chaine n'est pas un int
*	Entraine : -
*/
bool CStringUtil::STUisAnInt(char* pcSTUparam)
{
	if ('0' <= *pcSTUparam && *pcSTUparam <= '9')
	{
		return true;
	}
	return false;
}
/**
*	Entree : un pointeur sur une chaine de caracteres
*	Necessite : -
*	Sortie : un entier representant la taille de la chaine d'entree
*	Entraine : -
*/
int CStringUtil::STUgetLength(char* pcSTUparam)
{
	int iLength = 0;
	while (*pcSTUparam != '\0')
	{
		iLength++;
		pcSTUparam++;
	}
	return iLength;
}
