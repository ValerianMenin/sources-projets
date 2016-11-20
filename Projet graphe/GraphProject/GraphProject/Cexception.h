
#ifndef C_EXCEPTION_H
#define C_EXCEPTION_H

#include <iostream>

class Cexception
{
private:
	// Attributs
	char pcEXCvalue[254];
	bool bEXCendExecution;

public:
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : -
	*	Entraine : creation d'une erreur
	*/
	Cexception(void){ bool bEXCendExecution = true; };
	/**
	*	Entree :
	*		@param pcexception : une chaine de caracteres dans lequel est ecrit un message
	*		@param bEXCendExecution : un booleen optionnel qui indique si c'est une erreur pour "true" et ou un warning pour "false" (de base, c'est une erreur)
	*	Necessite : -
	*	Sortie : -
	*	Entraine : creation d'une erreur
	*/
	Cexception(char* pcexception, bool bEXCendExecution = true);
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : -
	*	Entraine : destruction de l'objet Cexception
	*/
	~Cexception(void){};

	// Methods
	/**
	*	Entree : 
	*		@param exception : notre message d'erreur
	*	Necessite : -
	*	Sortie : -
	*	Entraine : -
	*/
	void EXCsetpcEXCvalue(char exception){ *pcEXCvalue = exception; }
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : un pointeur sur la chaine de caractere dans laquelle est ecrit le message d'exception
	*	Entraine : -
	*/
	char* EXCgetpcEXCvalue(){ return pcEXCvalue; }
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : un booleen qui indique si c'est une erreur pour "true" et ou un warning pour "false" 
	*	Entraine : -
	*/
	bool EXCgetEndOfExecution(){ return bEXCendExecution; }

};

/**
*	Entree : une reference sur une erreur
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage de l'exception et fin de programme si c'est une erreur
*/
std::ostream &operator<<(std::ostream & OSTflux, Cexception & EXCparam);

#endif
