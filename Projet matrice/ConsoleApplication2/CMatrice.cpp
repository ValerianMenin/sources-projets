#include "stdafx.h"
#include "CMatrice.h"


/* exemple pour fonction template */
//template <class typeM > typeM CMatrice::MATLireValeur(int eblabla,  int eblabla2)



	template <class typeM> 
	typeM CMatrice::CMatrice<typeM>()
	{
		typeM[][] qMATmatrice;
	}
	template <class typeM> 
	typeM CMatrice::CMatrice<typeM>(CMatrice MATparam)
	{
		typeM[][] qMATmatrice;
		for (int eMATnbLigne = 0; eMATnbLigne < MATparam.qMATmatrice.lenght; eMATnbLigne++)
			for (int eMATnbColonne = 0; eMATnbColonne < MATparam.qMATmatrice[0].lenght; eMATnbColonne++)
				qMATmatrice[eMATnbLigne][eMATnbColonne] = MATparam.qMATmatrice[eMATnbLigne][eMATnbColonne];
	}
	template <class typeM> 
	typeM CMatrice::CMatrice<typeM>(int eMATnbLigne, int eMATnbColonne)
	{
		typeM[eMATnbLigne][eMATnbColonne] qMATmatrice;
	}
	template <class typeM> 
	typeM CMatrice::~CMatrice<typeM>()
	{
	}


	//typeM template <class typeM>CMatrice::qMATLireElement(int eMATligne, int eMATcolonne){return }
	//void template <class typeM>CMatrice::MATModifierElement<typeM>(typeM qMATparam, int eMATligne, int eMATcolonne){}
	template <class typeM>
	void CMatrice::MATAfficherMatrice<typeM>()
	{
		for (int eMATnbLigne = 0; eMATnbLigne < MATparam.qMATmatrice.lenght; eMATnbLigne++)
		{
			for (int eMATnbColonne = 0; eMATnbColonne < MATparam.qMATmatrice[0].lenght; eMATnbColonne++)
			{
				printf("%s%t", (String)qMATLireElement(eMATnbLigne, eMATnbColonne));
				//printf("%s%t", (10));
			}

		}
	}
	template <class typeM>
	CMatrice CMatrice::MATTransposer<typeM>()
	{
		// creer une matrice de type typeM avec le constructeur "CMatrice::CMatrice<typeM>(int eMATnbLigne, int eMATnbColonne)"
		// les param du constructeur sont (this[].length, this.length) pour initialiser la matrice transposée
		// parcourir toute la matrice courante et setMatriceTransposee 
	}

	//Surcharges Opérateurs
	template<class typeM>
	CMatrice CMatrice::operator +(CMatrice MATparam)
	{
		// exception si typeM n'est pas un nombre
		// execption si nbLigne OU nbColonne n'est pas identique entre le courant et MATparam
		// parcourir toute la matrice et additionner terme a terme
		// return matriceAdd
	}
	template<class typeM>
	CMatrice CMatrice::operator -(CMatrice MATparam)
	{
		// idem operateur +
	}
	template<class typeM> 
	CMatrice CMatrice::operator *(CMatrice MATparam)
	{

	}
	template<class typeM>
	CMatriceCMatrice::operator *(typeM qMATparam)
	{
	
	}
	template<class typeM>
	typeM CMatrice::operator * (CMatrice MATparam)
	{
	
	}
	template<class typeM>
	CMatrice CMatrice::operator / (typeM qMATparam)
	{
	
	}
	template<class typeM>
	CMatrice::operator = (CMatrice MATparam)
	{
	
	}
	template <class typeM>
	CMatrice CMatrice::operator += (CMatrice MATparam)
	{
	
	}

