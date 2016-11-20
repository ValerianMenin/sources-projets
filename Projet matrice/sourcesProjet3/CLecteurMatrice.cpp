#include "CLecteurMatrice.h"
#include <stdlib.h>

/*
 *	a la maniere d'un constructeur, la fonction initialise 
 *	@param le nom de fichier
 *	@param la matrice a lier au fichier
 */
CLecteurMatrice::CLecteurMatrice(char* pcLECparam, CMatrice<double> MATparam)
{
	pcLECnomFichier = pcLECparam;
	MATmatrice = MATparam;
}

/*
 *	@param le nom du fichier a lire
 *	@return l'objet CLectureMatrice qui regroupe le nom du fichier et la matrice contenue dans le fichier
 */
CMatrice<double> qLECcreateurMatriceCourante(char* pcLECparam)
{
	// on recopie le nom de fichier passe en parametre
	char* pcLECnomFichierTemp = pcLECparam;
	int eMATnbLigneTemp = 0;
	int eMATnbColonneTemp = 0;

	// ouverture en lecture du fichier
	ifstream ifs(pcLECparam, ifstream::in);
	//cout << "nom de fichier :" << pcLECparam << endl;
	CMatrice<double> MATmatriceCourante = CMatrice<double>();

	char lecteur[255];
	ifs >> lecteur;
	if (strncmp(lecteur, "TypeMatrice=", 12) == 0)//entete fichier
	{
		if (strncmp(&lecteur[12], "double", 6) == 0)//typeM
		{
			ifs >> lecteur;
			if (strncmp(lecteur, "NBLignes=", 9) == 0)//texte
			{
				// verifications
				//atoi permet d'avoir une conversion char vers int.
				//Mais il y a des erreurs possible dans la conversion (ex: "123t56" --> "123" et "y123" --> "0"). 
				//On va donc tester si tous les char sont des entiers.
				char* cLECnombreLigne = &lecteur[9];
				bool bLECnombreLigneEstUnInt = false;
				for (int i = 0; cLECnombreLigne[i] != '\0'; i++)
				{
					if ('0' <= cLECnombreLigne[i] && cLECnombreLigne[i] <= '9')//verification que c'est bien un nombre (pour eviter les erreurs/troncatures de atoi)
					{
						bLECnombreLigneEstUnInt = true; 
					}
					else
					{
						bLECnombreLigneEstUnInt = false;
						ifs.close(); 
						Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - nombre de lignes non valide");
						throw EXCcontenuFichierNonValide;
					}

				}
				if (bLECnombreLigneEstUnInt == true)
				{
					eMATnbLigneTemp = atoi(&lecteur[9]); //est un int donc affectation eMATnbLigneTemp
					ifs >> lecteur;
					if (strncmp(lecteur, "NBColonnes=", 11) == 0)//texte
					{
						char* cLECnombreColonne = &lecteur[11];
						bool bLECnombreColonneEstUnInt = false;
						for (int i = 0; cLECnombreColonne[i] != '\0'; i++)
						{
							if ('0' <= cLECnombreColonne[i] && cLECnombreColonne[i] <= '9')//verification que c'est bien un nombre (pour eviter les erreurs/troncatures de atoi)
							{
								bLECnombreColonneEstUnInt = true;
							}
							else
							{
								bLECnombreColonneEstUnInt = false;
								ifs.close(); 
								Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - nombre de colonne non valide");
								throw EXCcontenuFichierNonValide;
							}
						}
						if (bLECnombreColonneEstUnInt == true)
						{
							eMATnbColonneTemp = atoi(&lecteur[11]); //est un int donc affectation eMATnbColonneTemp
							ifs >> lecteur;
							if (strncmp(lecteur, "Matrice=[", 9) == 0)//texte debut matrice
							{
								MATmatriceCourante = CMatrice<double>(eMATnbColonneTemp, eMATnbLigneTemp);// creation de la matrice
								//cout << "nombre de ligne   : " << MATmatrice.eMATLireNbLigne() << endl;
								//cout << "nombre de colonne : " << MATmatrice.eMATLireNbColonne() << endl;

								// on va parcourir toute la matrice du fichier
								for (int eIndexLigne = 0; eIndexLigne < eMATnbLigneTemp; eIndexLigne++)
									for (int eIndexColonne = 0; eIndexColonne < eMATnbColonneTemp; eIndexColonne++)
									{
										ifs >> lecteur;
										bool bLECnombreEstUnDouble;
										bLECnombreEstUnDouble = bLECestUnDouble(lecteur);
										if (bLECnombreEstUnDouble == true) // si les nombre est bien un double (ou int, short ...) ...
										{
											MATmatriceCourante[eIndexColonne][eIndexLigne] = atof(lecteur);// ...on le stock dans la matrice
										}
										else
										{
											ifs.close();
											/*cout << "problemeDebut\n" << endl;
											MATmatriceCourante = CMatrice<double>(0);
											cout << MATmatriceCourante << endl;
											cout << MATmatriceCourante.eMATLireNbColonne() << endl << MATmatriceCourante.eMATLireNbLigne() << endl;
											cout << "problemeFin\n" << endl;*/
											Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - le nombre dans la matrice n\'est pas valide");
											throw EXCcontenuFichierNonValide;
										}
									}
							}
							ifs >> lecteur;
							if (strncmp(lecteur, "]", 1) != 0)//texte fin matrice
							{
								ifs.close(); 
								Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - contenu texte non valide apres avoir rempli la matrice");
								throw EXCcontenuFichierNonValide;
							}
						}
					}
				}
			}
			else
			{
				ifs.close();
				Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - contenu texte non valide");
				throw EXCcontenuFichierNonValide;
			}
		}
		else
		{
			ifs.close(); 
			Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - typeM non valide");
			throw EXCcontenuFichierNonValide;
		}
	}
	else
	{
		ifs.close(); 
		Cexception EXCcontenuFichierNonValide("Erreur - lecture fichier - entete non valide");
		throw EXCcontenuFichierNonValide;
	}
	return MATmatriceCourante;
}

CMatrice<double> qLECLectureFichierMatrice(char* pcLECnomFichier)
{
	CMatrice<double> MATlecteur = CMatrice<double>();
	try
	{
		MATlecteur = qLECcreateurMatriceCourante(pcLECnomFichier);
		//cout << "ceci est la matrice - dans le CLectureMatrice - LECLectureFichierMatrice\n";
		//cout << MATlecteur;
	}
	catch (ifstream::failure e)
	{
		cerr << "Erreur - CLecteurMatrice::CLecteurMatrice(char*) - ouverture/lecture du fichier" << endl;
	}
	catch (Cexception EXCcontenuFichierNonValide)
	{//pas d affichage du message car il va etre affiche et traite dans le main
		//CMatrice<double>MATlecteur(0);
		throw EXCcontenuFichierNonValide;
	}
	cout << "fin de lecture" << endl;
	return MATlecteur;
}

bool bLECestUnDouble(char* lecteur)
{
	bool bLECnombreEstUnDouble = false;
	bool bLECpointTrouve = false; // pour le double, si il y en a plus que 2 : erreur
	for (int i = 0; lecteur[i] != '\0'; i++)
	{
		if (i == 0 && lecteur[0] == '-')
		{
			i++;
		}
		if (('0' <= lecteur[i] && lecteur[i] <= '9') || lecteur[i] == '.')//verification que c'est bien un nombre (pour eviter les erreurs/troncatures de atof)
		{
			if (lecteur[i] == '.')// si c'est un point ...
			{
				if (bLECpointTrouve == false)// ...et que nous n'avons pas encore trouve de point...
				{
					bLECpointTrouve = true;// ... alors on dit qu'on l'a trouve
				}
				else// si on en trouve un pour la deuxieme fois, alors c'est une erreur
				{
					bLECnombreEstUnDouble = false;
				}
			}
			bLECnombreEstUnDouble = true;
		}
		else
		{
			bLECnombreEstUnDouble = false;
		}
	}
	return bLECnombreEstUnDouble;
}