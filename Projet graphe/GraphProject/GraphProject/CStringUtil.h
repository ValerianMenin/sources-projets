
#ifndef C_STRING_UTIL
#define C_STRING_UTIL

#include "Cexception.h"
#include "CGraph.h"

class CStringUtil
{
	public:
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : creation d'un objet CStringUtil
		*/
		CStringUtil(){}
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : destruction de l'objet CStringUtil
		*/
		~CStringUtil(){}

		/**
		*	Entree : un pointeur sur une chaine de caracteres
		*	Necessite : -
		*	Sortie : un booleen
		*		@return true si la chaine est un int
		*		@return false si la chaine n'est pas un int
		*	Entraine : -
		*/
		static bool STUisAnInt(char* pcSTUparam);
		/**
		*	Entree : un pointeur sur une chaine de caracteres
		*	Necessite : -
		*	Sortie : un entier representant la taille de la chaine d'entree
		*	Entraine : -
		*/
		static int STUgetLength(char* pcSTUparam);
};

#endif
