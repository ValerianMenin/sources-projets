#pragma once
class Cexception
{
private:
	//Variables
	unsigned int uiEXCValeur;

public:
	//Cons & Dest
	Cexception(void);
	Cexception(unsigned int exception);
	~Cexception(void);

	//Méthodes
	void EXCModifierException(unsigned int exception);
	unsigned int eEXCLireException();

};
