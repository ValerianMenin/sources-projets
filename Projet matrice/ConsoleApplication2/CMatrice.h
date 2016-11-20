#ifndef C_MAT
#define C_MAT
	#pragma once
template <class typeM>
class CMatrice
{
private:
	//Variables
	typeM qMATmatrice[][];
public:
	//Constructeurs & Destructeur
	CMatrice();
	CMatrice<typeM>(typeM MATparam);
	CMatrice<typeM>(int eMATnbLigne, int eMATnbColonne);
	~CMatrice<typeM>();

	//Surcharges Opérateurs
	CMatrice operator+(CMatrice MATparam);
	CMatrice operator-(CMatrice MATparam);
	CMatrice operator*(CMatrice MATparam);
	CMatrice operator*(typeM qMATparam);
	typeM operator*(CMatrice MATparam);
	CMatrice operator/(typeM qMATparam);
	CMatrice operator=(CMatrice MATparam);
	CMatrice operator+=(CMatrice MATparam);

	//Fonctions
	typeM CMatrice::qMATLireElement(int eMATligne, int eMATcolonne){ return qMATmatrice[eMATligne][eMATcolonne]; }
	void MATModifierElement(typeM qMATparam, int eMATligne, int eMATcolonne){ qMATmatrice[eMATligne][eMATcolonne] = qMATparam; }
	void MATAfficherMatrice();
	CMatrice MATTransposer();
};

#include "CMatrice.cpp"
#endif