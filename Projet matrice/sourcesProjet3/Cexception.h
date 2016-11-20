#pragma once
#include <iostream>


using namespace std;

class Cexception
{
private:
	//Variables
	char cEXCValeur[254];

public:
	//Cons & Dest
	Cexception(void);
	Cexception(char* exception);
	~Cexception(void);

	//Méthodes
	void EXCModifierException(char exception){ *cEXCValeur = exception; }
	char* pcEXCLireException(){ return cEXCValeur; }

};

std::ostream &operator<<(std::ostream & OSTflux, Cexception & EXCparam);


