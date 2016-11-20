#ifndef C_MAT
#define C_MAT
#pragma once
#include "Cexception.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace std;

/*
 *
 *	La syntaxe globale utilisee pour acceder a une case de matrice est la suivante : numero de colonne suivi du numero de ligne !
 *
 */
template <class typeM>
class CMatrice
{
private:
	//Variables
	typeM** ppqMATmatrice;
	int eMATnbColonne;
	int eMATnbLigne;

public:
	//Constructeurs & Destructeur
	CMatrice<typeM>();
	CMatrice<typeM>(int eMATnbColonne, int eMATnbLigne, typeM qMATparam[]);
	CMatrice<typeM>(CMatrice<typeM> & MATparam);
	CMatrice<typeM>(typeM qMATparam);
	CMatrice<typeM>(const int eMATnbColonne, const int eMATnbLigne);
	~CMatrice<typeM>();

	//Surcharges Opérateurs
	CMatrice<typeM> operator+(CMatrice<typeM> & MATparam);
	CMatrice<typeM> operator-(CMatrice<typeM> & MATparam);
	CMatrice<typeM> operator*(typeM qMATparam);
	CMatrice<typeM> operator*(CMatrice<typeM> & MATparam); // multiplier matrice par matrice
	CMatrice<typeM> operator/(typeM qMATparam);
	CMatrice<typeM> operator=(CMatrice<typeM> & MATparam);
	CMatrice<typeM> operator+=(CMatrice<typeM> & MATparam);
	CMatrice<typeM> operator-=(CMatrice<typeM> & MATparam);
	typeM* operator[](int iCol) { return ppqMATmatrice[iCol]; } // pour utiliser cet operateur, typeM = type_primitif

	//Fonctions
	typeM CMatrice::qMATLireElement(int eMATcolonne, int eMATligne){ return ppqMATmatrice[eMATcolonne][eMATligne]; }
	void CMatrice::MATModifierElement(typeM qMATparam, int eMATcolonne, int eMATligne);
	int CMatrice::eMATLireNbColonne(){ return eMATnbColonne; }
	int CMatrice::eMATLireNbLigne(){ return eMATnbLigne; }
	void MATAfficherMatrice();
	CMatrice<typeM> MATTransposer();

};

// surcharge d'operateur de CMatrice<typeM> avec un typeM (et inversement)
template <class typeM> CMatrice<typeM> operator*(typeM qMATparam, CMatrice<typeM> & MATparam);
// surcharge de flux std
template <class typeM> 
std::ostream &operator<<(std::ostream & OSTflux, CMatrice<typeM> & MATparam);

#include "CMatrice.cpp"

#endif