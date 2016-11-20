
#include <iostream> // pour cout 
#include  <cstdarg>
#include "Cexception.h"
#include "CMatrice.h"
#include "CLecteurMatrice.h"

void testManipulationCMatrice()
{
	// initialisation matrice
	CMatrice<int> test4 = CMatrice<int>(5, 2);

	// modifier matrice
	test4.MATModifierElement(1, 0, 0);
	test4.MATModifierElement(2, 1, 0);
	test4.MATModifierElement(3, 2, 0);
	test4.MATModifierElement(4, 3, 0);
	test4.MATModifierElement(5, 4, 0);
	test4.MATModifierElement(6, 0, 1);
	test4.MATModifierElement(7, 1, 1);
	test4.MATModifierElement(8, 2, 1);
	test4.MATModifierElement(9, 3, 1);
	test4.MATModifierElement(10, 4, 1);

	// initialisation matrice
	CMatrice<int> test6 = CMatrice<int>(5, 2);

	// modifier matrice
	test6.MATModifierElement(10, 0, 0);
	test6.MATModifierElement(20, 1, 0);
	test6.MATModifierElement(30, 2, 0);
	test6.MATModifierElement(40, 3, 0);
	test6.MATModifierElement(50, 4, 0);
	test6.MATModifierElement(60, 0, 1);
	test6.MATModifierElement(70, 1, 1);
	test6.MATModifierElement(80, 2, 1);
	test6.MATModifierElement(90, 3, 1);
	test6.MATModifierElement(100, 4, 1);

	// affichage matrice
	cout << "test4" << endl;
	cout << test4;
	cout << "test6" << endl;
	cout << test6;

	cout << "transpo(test4)" << endl;
	CMatrice<int> transpo = CMatrice<int>(test4.MATTransposer());
	cout << transpo;

	cout << "test7 = test4+test6\n" << endl;
	CMatrice<int> test7(test4+test6);
	cout << test7;

	cout << "test8 = test4-test6\n" << endl;
	CMatrice<int> test8(test4-test6);
	cout << test8;

	cout << "test4 += test4\n" << endl;
	test4 += test4;
	cout << test4;

	//cout << "test9(test4) << endl;
	//CMatrice<int> test9(test4);
	//test9.MATAfficherMatrice();

	/*cout << "test10 = 20" << endl;
	CMatrice<int> test10(20);
	test10.MATAfficherMatrice();*/
	
	// test4*a
	cout << "a = 2\ntest4 = test4*a" << endl;
	test4 = test4 * 2;
	cout << test4;

	// a*test4
	cout << "a = 4\ntest4 = a*test4" << endl;
	test4 = 4 * test4;
	cout << test4;

	// test4/8
	cout << "a = 8\ntest4 = test4/8" << endl;
	test4 = test4 / 8;
	cout << test4;

	//cout << test4[2][1] << endl;

	CMatrice<int> test11(5, 1);
	test11.MATModifierElement(1, 0, 0);
	test11.MATModifierElement(2, 1, 0);
	test11.MATModifierElement(3, 2, 0);
	test11.MATModifierElement(4, 3, 0);
	test11.MATModifierElement(5, 4, 0);

	CMatrice<int> test12(test11.MATTransposer());
	cout << "test11\n" << test11 << "test12\n" << test12 << endl;

	// test11 * test12
	cout << "test11 * test12" << endl;
	cout << test11 * test12;

	// constructeur avec tableau
		//creer une liste de typeM
		//faire appel au constructeur CMatrice<typeM> test13(tableau)

	int etableau[6] = { 0, 1, 2, 3, 4, 5};
	CMatrice<int> test13(2, 3, etableau);
	cout << "test13" << endl << test13 << endl;

	cout << "test d'affichage d'une erreur :" << endl;
	test13.MATModifierElement(5, 3, 3);



	cout << endl << "=====================================================";
	cout << endl << "<=== tests unitaire - manipulation CMatrice : ok ===>" << endl;
}

void testChangementTailleMatrice()
{
	double etableau1[4] = { 1, 2, 3, 4 };
	CMatrice<double> test13(2, 2, etableau1);
	cout << "test13" << endl << test13 << endl;

	double etableau2[6] = { 5, 3, 6, 1, -2, 8};
	CMatrice<double> test14(3, 2, etableau2);
	cout << "test14" << endl << test14 << endl;

	cout << "avant test13=test14" << endl;
	test13 = test14;
	cout << "apres test13=test14" << endl;
	cout << "test13=test14" << endl << test13 << endl;
}

void testUnitaireLectureFichier()
{
	char* pctest = "fichier4.txt";
	qLECLectureFichierMatrice(pctest);
	pctest = "fichier5.txt";
	qLECLectureFichierMatrice(pctest);
	pctest = "fichier6.txt";
	qLECLectureFichierMatrice(pctest);

	cout << endl << "<=== tests unitaire - lecture fichier CMatrice : ok ===>";
	cout << endl << "========================================================" << endl;
}

void testFonctionVariadic(int nbMembre, int i ...)
{
	va_list args;
	va_start(args, nbMembre);
	//int z = 
	while (nbMembre != 0)
	{
		cout << va_arg(args, int) << "\t";
		nbMembre--;
	}
	va_end(args);
}
void appelTestVariadic()
{
	int i = 1;
	int j = 2;
	int k = 3;
	int l = 4;
	int m = 5;
	testFonctionVariadic(6, i, j, k, l, m, 0); // 6 param
}

void testLectureFichiersMultiples()
{

	//char* etableau[6] = { "fichier1.txt", "fichier2.txt", "fichier3.txt", "fichier4.txt", "fichier5.txt", "fichier6.txt" };

	// demander le nombre de fichier en entree nbDeFichiers
	//cin << ........

	CMatrice<char*> test13(1, 6); //initialiser la matrice de noms de fichiers
	//parcourir la matrice de 0 a nbDeFichiers-1
		//cin << ... //le nom du fichier de lecture
		//
	cout << "test13" << endl << test13 << endl;


}

void testMatriceDeMatrice()
{
	int etableau[6] = { 0, 1, 2, 3, 4, 5 };
	CMatrice<int> test20(2, 3, etableau);
	cout << "test20" << endl << test20 << endl;

	int etableau2[6] = { 5, 6, 7, 8, 9, 10 };
	CMatrice<int> test21(2, 3, etableau2);
	cout << "test21" << endl << test21 << endl;

	cout << "declaration MatriceDeMatrice\n";
	//CMatrice<int> MATmatriceDeMatrice[2];//1er solution : tablequ de matrice
	CMatrice<CMatrice<int>> MATmatriceDeMatrice(2, 1);//2eme solution : matrice de matrice
	//MATmatriceDeMatrice.MATModifierElement(test20, 0, 0);

	cout << "MATmatriceDeMatrice[0][0] = test20\n";
	MATmatriceDeMatrice[0][0] = test20;
	cout << "MATmatriceDeMatrice[1][0] = test21\n";
	MATmatriceDeMatrice[1][0] = test21;

	test20 += test21;


	cout << "la matrice 1\n" << MATmatriceDeMatrice[0][0] << endl;
	cout << "la matrice 2\n" << MATmatriceDeMatrice[1][0] << endl;
	cout << "fin de fonction\n";

}

void manipulationMatriceAvecFichier(int argc, char* argv[])
{
	cout << "avant\n";
	for (int i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}
	cout << "apres\n";

	try
	{
		if (argc < 1)
		{
			Cexception EXCaucunFichierEnLecture("Erreur - manipulationMatriceAvecFichier - aucun fichier en entree");
			throw EXCaucunFichierEnLecture;
		}
		else
		{
			int eindex;
			if (argc == 2)// si il n'y a qu'un parametre, on previent l'utilisateur que c'est etrange mais on effectue quand meme les calculs
				cout << "Warning - manipulationMatriceAvecFichier - un seul fichier en entree" << endl;
			cout << "eee\n";
			// allocation d'une matrice MATlisteMatrice de taille (argc-2, 1)
			// parcours des arguments d'entree de 1 a argc-1
				// recopie a la matrice de argv[i] dans MATlisteMatrice[i-1][0]
			CMatrice<CMatrice<double>> MATlisteMatrice(argc - 1, 1);
			for (eindex = 0; eindex < argc-2; eindex++)
			{
				//MATlisteMatrice[eindex][0] = argv[eindex].
				//cout << argv[eindex] << endl;
			}

			//demmander a l'utilisateur de rentrer un nombre "c"
				//verifier que "c" est un double
					//si c n'est pas un double, on a donc c==0. Si c==0 : afficher une erreur, ne pas executer le reste du code
				//stockage de "c"

			// parcourir MATlisteMatrice
				//afficher MATlisteMatrice[i][0]*c

			// parcourir MATlisteMatrice
				//afficher MATlisteMatrice[i][0]/c

			//allouer une copier MATsomme de argv[1er element]
			// parcourir MATlisteMatrice du 2nd element a la fin
				//MATsomme+=MATlisteMatrice[i][0]
			//afficher MATsomme

			//allouer une copier MATsommeAlternee de argv[1er element]
			// parcourir MATlisteMatrice du 2nd element a la fin
				//si(i%2==1)
					//MATsommeAlternee+=MATlisteMatrice[i][0]
				//sinon
					//MATsommeAlternee-=MATlisteMatrice[i][0]
			//afficher MATsommeAlternee

			//allouer une matrice MATproduit = 1er element * 2nd element /!\ il faut qu'il y ai au moins 2 fichiers en param.
			// parcourir MATlisteMatrice du 3eme element au dernier element
				//MATproduit = MATproduit*MATlisteMatrice[i][0]
			//afficher MATproduit

			cout << argc;

		}
	}
	catch (Cexception EXCerreurCourrante)
	{
		cerr << EXCerreurCourrante << endl;
	}
	
}

int main(int argc, char* argv[])
{
	//==================================================
	// code test =======================================
	//==================================================

	//testManipulationCMatrice();

	//testUnitaireLectureFichier();

	//testChangementTailleMatrice();

	//appelTestVariadic();

	//testLectureFichiersMultiples();

	//testMatriceDeMatrice();

	//=================================================
	//manipulationMatriceAvecFichier(argc,* argv[]); ==
	//=================================================

	//cout << "avant\n";
	//for (int i = 0; i < argc; i++)
	//{
	//	cout << argv[i] << endl;
	//}
	//cout << "apres\n";


	cout << "nombre d arguments : " << argc << endl;

	try
	{
		if (argc < 1)
		{
			Cexception EXCaucunFichierEnLecture("Erreur - manipulationMatriceAvecFichier - aucun fichier en entree");
			throw EXCaucunFichierEnLecture;
		}
		else
		{
			int eindex;
			bool bFichiersValides = true;
			if (argc == 2)// si il n'y a qu'un parametre, on previent l'utilisateur que c'est etrange mais on effectue quand meme les calculs
				cout << "Warning - manipulationMatriceAvecFichier - un seul fichier en entree" << endl;

			// allocation d'une matrice MATlisteMatrice de taille (argc-2, 1)
			// parcours des arguments d'entree de 1 a argc-1
			// recopie a la matrice de argv[i] dans MATlisteMatrice[i-1][0]
			CMatrice<CMatrice<double>> MATmatriceDeMatrices(argc - 1, 1);//allocation de la matrice de matrices
			try
			{
				for (eindex = 1; eindex < argc; eindex++)
				{
					MATmatriceDeMatrices[eindex - 1][0] = qLECLectureFichierMatrice(argv[eindex]);
					cout << "fichier " << argv[eindex] << endl << MATmatriceDeMatrices[eindex - 1][0] << endl;
				}
			}
			catch (Cexception EXCerreurCourante)
			{
				cout << "q\n";
				cerr << EXCerreurCourante << endl;
				cout << "t\n";
				bFichiersValides = false;
				cout << "p\n";
			}

			if (bFichiersValides == true)//si il n'y a pas eu de problemes sur la lecture des fichiers.
			{
				//demmander a l'utilisateur de rentrer un nombre "c"
				//verifier que "c" est un double
				//stockage de "c"
				char pcEntreeUtilisateur[64];
				cout << "Veuillez saisir un double : "; cin >> pcEntreeUtilisateur; cout << endl;
				if (bLECestUnDouble(pcEntreeUtilisateur) == true)
				{
					double dEntree = atof(pcEntreeUtilisateur);

					cout << "produit par le scalaire c=" << dEntree << endl;
					for (eindex = 1; eindex < argc; eindex++)// produit par un scalaire
					{
						cout << MATmatriceDeMatrices[eindex - 1][0] * dEntree << endl;
					}

					//si c n'est pas un double, on a donc c==0. Si c==0 : afficher une erreur, ne pas executer le reste du code
					if (dEntree != 0)// division par un scalaire
					{
						cout << "division par le scalaire c=" << dEntree << endl;
						for (eindex = 1; eindex < argc; eindex++)
						{
							cout << MATmatriceDeMatrices[eindex - 1][0] / dEntree << endl;
						}
					}
					else
					{
						Cexception EXCerreurCourante("Erreur - entree standard - division par zero");
						throw EXCerreurCourante;
					}
				}
				else
				{
					Cexception EXCerreurCourante("Erreur - lecture entree standard - le nombre n'est pas un double");
					throw EXCerreurCourante;
				}

				//allouer une copier MATsomme de argv[1er element]
				// parcourir MATlisteMatrice du 2nd element a la fin
				//MATsomme+=MATlisteMatrice[i][0]
				//afficher MATsomme
				cout << "somme des matrices" << endl;
				CMatrice<double> MATsomme(MATmatriceDeMatrices[0][0]);
				for (eindex = 1; eindex < argc - 1; eindex++)
				{
					MATsomme += MATmatriceDeMatrices[eindex][0];
				}
				cout << MATsomme << endl;

				//allouer une copier MATsommeAlternee de argv[1er element]
				// parcourir MATlisteMatrice du 2nd element a la fin
				//si(i%2==1)
				//MATsommeAlternee+=MATlisteMatrice[i][0]
				//sinon
				//MATsommeAlternee-=MATlisteMatrice[i][0]
				//afficher MATsommeAlternee
				cout << "somme alternee des matrices" << endl;
				CMatrice<double> MATsommeAlternee(MATmatriceDeMatrices[0][0]);
				for (eindex = 1; eindex < argc - 1; eindex++)
				{
					if (eindex % 2 == 0)
					{
						MATsommeAlternee += MATmatriceDeMatrices[eindex][0];
					}
					else
						MATsommeAlternee -= MATmatriceDeMatrices[eindex][0];
				}
				cout << MATsommeAlternee;

				//allouer une matrice MATproduit = 1er element * 2nd element /!\ il faut qu'il y ai au moins 2 fichiers en param.
				// parcourir MATlisteMatrice du 3eme element au dernier element
				//MATproduit = MATproduit*MATlisteMatrice[i][0]
				//afficher MATproduit			
				cout << "produit des matrices" << endl;
				CMatrice<double> MATproduit(MATmatriceDeMatrices[0][0]);
				for (eindex = 1; eindex < argc - 1; eindex++)
				{
					MATproduit = MATproduit*MATmatriceDeMatrices[eindex][0];
				}
				cout << MATproduit;

				//cout << MATmatriceDeMatrices << endl;

			}
		}
	}
	catch (Cexception EXCerreurCourante)
	{
		cerr << EXCerreurCourante << endl;
	}

	cout << "fin de traitement\n";

	return 0;
}

