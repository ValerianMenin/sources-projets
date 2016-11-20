
// Constructeurs - destructeur
template <class typeM>
CMatrice<typeM>::CMatrice()
{
	eMATnbColonne = 0;
	eMATnbLigne = 0;
}

template <class typeM>
CMatrice<typeM>::CMatrice(int eMATnewNbColonne, int eMATnewNbLigne, typeM qMATparam[])
{

	eMATnbColonne = eMATnewNbColonne;
	eMATnbLigne = eMATnewNbLigne; 
	ppqMATmatrice = new typeM*[eMATnewNbColonne];
	for (int i = 0; i < eMATnewNbColonne; i++)
	{
		ppqMATmatrice[i] = new typeM[eMATnewNbLigne];
	}

	try
	{
		if (eMATnbColonne * eMATnbLigne >= sizeof(qMATparam) / sizeof(typeM))
		{
			int eMATindiceDuTableau = 0;
			for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
				for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
				{
					ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = qMATparam[eMATindiceDuTableau];
					eMATindiceDuTableau++;
				}
		}
		if (eMATnbColonne * eMATnbLigne < sizeof(qMATparam) / sizeof(typeM) + 1)
		{
			Cexception EXCemplacementNonValide("Erreur - CMatrice(int eMATnbColonne, int eMATnbLigne, typeM qMATparam[]) - depacement matrice");
			throw EXCemplacementNonValide;
		}
	}
	catch (Cexception EXCemplacementNonValide)
	{
		cerr << EXCemplacementNonValide << endl;
	}
	
}

template <class typeM>
CMatrice<typeM>::CMatrice(typeM qMATparam)
{
	eMATnbColonne = 1;
	eMATnbLigne = 1;
	ppqMATmatrice = new typeM*[eMATnbColonne];
	ppqMATmatrice[0] = new typeM[eMATnbLigne];
	ppqMATmatrice[0][0] = qMATparam;
}

template <class typeM>
CMatrice<typeM>::CMatrice(CMatrice<typeM> & MATparam)
{	
	eMATnbColonne = MATparam.eMATnbColonne;
	eMATnbLigne = MATparam.eMATnbLigne; 

	ppqMATmatrice = new typeM*[eMATnbColonne];
	for (int i = 0; i < eMATnbColonne; i++)
	{
		ppqMATmatrice[i] = new typeM[eMATnbLigne];
	}

	for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
		for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
			ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = MATparam.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne];
}

template <class typeM>
CMatrice<typeM>::CMatrice(int eMATnewNbColonne, int eMATnewNbLigne)
{
	ppqMATmatrice = new typeM*[eMATnewNbColonne];
	for (int i = 0; i < eMATnewNbColonne; i++)
	{
		ppqMATmatrice[i] = new typeM[eMATnewNbLigne];
	}
	eMATnbColonne = eMATnewNbColonne;
	eMATnbLigne = eMATnewNbLigne;
}

template <class typeM>
CMatrice<typeM>::~CMatrice()
{
	for (int i = 0; i < eMATnbColonne; i++)
	{
		delete[] ppqMATmatrice[i];
	}
	delete[] ppqMATmatrice;
}

// Methodes
template <class typeM>
void CMatrice<typeM>::MATModifierElement(typeM qMATparam, int eMATcolonne, int eMATligne)
{ 
	try
	{
		if ((0 <= eMATcolonne && eMATcolonne < eMATLireNbColonne()) && (0 <= eMATligne && eMATligne < eMATLireNbLigne()))
		{
			ppqMATmatrice[eMATcolonne][eMATligne] = qMATparam;
		}
		else
		{
			Cexception EXEemplacementNonValide("Erreur - MATModifierElement - l\'emplacement n\'existe pas");
			throw EXEemplacementNonValide;
		}
	}
	catch (Cexception EXEemplacementNonValide)
	{
		cerr << EXEemplacementNonValide << endl;
	}
	
}

template <class typeM>
void CMatrice<typeM>::MATAfficherMatrice()
{
	for (int eMATindiceLigne = 0; eMATindiceLigne < eMATLireNbLigne(); eMATindiceLigne++)
	{
		for (int eMATindiceColonne = 0; eMATindiceColonne < eMATLireNbColonne(); eMATindiceColonne++)
			cout << qMATLireElement(eMATindiceColonne, eMATindiceLigne) << '\t';
		cout << endl;
	}
}

template <class typeM>
CMatrice<typeM> CMatrice<typeM>::MATTransposer()
{
	CMatrice<typeM> MATtranspose = CMatrice<typeM>(eMATnbLigne, eMATnbColonne);
	for (int i = 0; i < MATtranspose.eMATnbColonne; i++)
		for (int j = 0; j < MATtranspose.eMATnbLigne; j++)
			MATtranspose.MATModifierElement(qMATLireElement(j, i), i, j);
	return MATtranspose;
}

//Surcharges Opérateurs
template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator+(CMatrice<typeM> & MATparam)
{
	CMatrice<typeM> MATresultat(eMATnbColonne, eMATnbLigne);
	try
	{
		if (MATparam.eMATnbColonne == eMATnbColonne && MATparam.eMATnbLigne == eMATnbLigne)
		{
			for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
				for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
					MATresultat.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] + MATparam.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne];
		}
		else
		{
			Cexception EXEemplacementNonValide("Erreur - operator+ - la taille des matrices n\'est pas identique");
			throw EXEemplacementNonValide;
		}
	}
	catch (Cexception EXEemplacementNonValide)
	{
		cerr << EXEemplacementNonValide << endl;
	}
	return MATresultat;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator-(CMatrice<typeM> & MATparam)
{
	CMatrice<typeM> MATresultat(eMATnbColonne, eMATnbLigne);
	try
	{
		if (MATparam.eMATnbColonne == eMATnbColonne && MATparam.eMATnbLigne == eMATnbLigne)
		{
			for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
				for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
					MATresultat.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] - MATparam.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne];
		}
		else
		{
			Cexception EXEemplacementNonValide("Erreur - operator- - la taille des matrices n\'est pas identique");
			throw EXEemplacementNonValide;
		}
	}
	catch (Cexception EXEemplacementNonValide)
	{
		cerr << EXEemplacementNonValide << endl;
	}
	
	return MATresultat;
}

// multiplication de deux matrices entre elles
template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator *(CMatrice & MATparam)
{
	CMatrice<typeM> MATresultat(MATparam.eMATLireNbColonne(), eMATnbLigne); // la nouvelle matrice
	MATresultat = MATresultat - MATresultat; // matrice vide pour les types primitifs
	try
	{
		if (eMATnbColonne == MATparam.eMATLireNbLigne())
		{
			for (int eMATindiceLigne1 = 0; eMATindiceLigne1 < eMATnbLigne; eMATindiceLigne1++)
				for (int eMATindiceColonne2 = 0; eMATindiceColonne2 < MATparam.eMATLireNbColonne(); eMATindiceColonne2++)
					for (int eMATindiceColonne1 = 0; eMATindiceColonne1 < eMATnbColonne; eMATindiceColonne1++)
					{
						//cout << MATresultat << endl;
						MATresultat[eMATindiceColonne2][eMATindiceLigne1] += ppqMATmatrice[eMATindiceColonne1][eMATindiceLigne1] * MATparam.ppqMATmatrice[eMATindiceColonne2][eMATindiceColonne1];
					}
		}
		else
		{
			Cexception EXEemplacementNonValide("Erreur - operator* - la taille des matrices ne permet pas leur multiplication");
			throw EXEemplacementNonValide;
		}
	}
	catch (Cexception EXEemplacementNonValide)
	{
		cerr << EXEemplacementNonValide << endl;
	}
	return MATresultat;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator*(typeM qMATparam)
{
	CMatrice<typeM> MATresultat(eMATnbColonne, eMATnbLigne);
	for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
		for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
			MATresultat.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] * qMATparam;
	return MATresultat;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator/(typeM qMATparam)
{
	CMatrice<typeM> MATresultat(eMATnbColonne, eMATnbLigne);
	for (int eMATindiceLigne = 0; eMATindiceLigne < eMATnbLigne; eMATindiceLigne++)
		for (int eMATindiceColonne = 0; eMATindiceColonne < eMATnbColonne; eMATindiceColonne++)
			MATresultat.ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] = ppqMATmatrice[eMATindiceColonne][eMATindiceLigne] / qMATparam;
	return MATresultat;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator=(CMatrice<typeM> & MATparam)
{
	// si les tailles de tableaux ne sont pas identiques : supprimer tableau puis reallouer le bon tableau pour commencer la copie
	if (MATparam.eMATLireNbColonne() != eMATnbColonne || MATparam.eMATLireNbLigne() != eMATnbLigne)
	{
		// suppression du talbeau de tableaux
		for (int eCol = 0; eCol < eMATnbColonne; eCol++)
			delete[] ppqMATmatrice[eCol];

		eMATnbColonne = MATparam.eMATnbColonne;
		eMATnbLigne = MATparam.eMATnbLigne;
		
		// on doit realouer la matrice car les tailles des 2 matrices ne sont pas forcement identiques
		ppqMATmatrice = new typeM*[eMATnbColonne];
		for (int i = 0; i < eMATnbColonne; i++)
			ppqMATmatrice[i] = new typeM[eMATnbLigne];
	}

	// copie de la matrice membre a membre
	for (int eLig = 0; eLig < eMATnbLigne; eLig++)
		for (int eCol = 0; eCol < eMATnbColonne; eCol++)
			ppqMATmatrice[eCol][eLig] = MATparam.qMATLireElement(eCol, eLig);
	return *this;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator+=(CMatrice<typeM> & MATparam)
{
	*this = *this + MATparam;
	return *this;
}

template<class typeM>
CMatrice<typeM> CMatrice<typeM>::operator-=(CMatrice<typeM> & MATparam)
{
	*this = *this - MATparam;
	return *this;
}

template<class typeM>
CMatrice<typeM> operator*(typeM qMATparam, CMatrice<typeM> & MATparam)
{
	CMatrice<typeM> MATresultat(MATparam);
	for (int eMATindiceLigne = 0; eMATindiceLigne < MATparam.eMATLireNbLigne(); eMATindiceLigne++)
		for (int eMATindiceColonne = 0; eMATindiceColonne < MATparam.eMATLireNbColonne(); eMATindiceColonne++)
			MATresultat.MATModifierElement(MATparam.qMATLireElement(eMATindiceColonne, eMATindiceLigne)* qMATparam, eMATindiceColonne, eMATindiceLigne);
	return MATresultat;
}

template <class typeM>
std::ostream &operator<<(std::ostream & OSTflux, CMatrice<typeM> & MATparam)
{
	MATparam.MATAfficherMatrice();
	return cout;
}

