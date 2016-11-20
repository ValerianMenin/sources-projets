
#include "CGraph.h"
#include <stdlib.h> //to use realloc

/**
*	Entree : -
*	Necessite : ne pas etre utilise, l'utilisation normale est celle par le constructeur avec un fichier d'entree
*	Sortie : -
*	Entraine : creation d'un nouveau graph qui est vide et oriente
*/
CGraph::CGraph()
{
	iGRAnbOfNode = 0;
	ppnGRAnodeList = nullptr;
	bGRAisDirected = true;
}
/**
*	Entree : une chaine de caractere correspondant en nom du fichier dans lequel se trouve un graph
*	Necessite : -
*	Sortie : -
*	Entraine :
*		creation d'un nouveau graph oriente ayant les valeurs du fichier
*		OU (Cexception de type Erreur si il y a une erreur dans la lecture, acces ... )
*/
CGraph::CGraph(char* pcGRAfileName)
{
	//initialisation des attributs du graph comme le constructeur par defaut
	iGRAnbOfNode = 0;
	ppnGRAnodeList = nullptr;
	bGRAisDirected = true;//oriente car il n'y a pas d'informations a ce sujet dans le fichier fournis

	char reader[255];//la chaine de char dans laquel on stock la ligne lue

	//ouverture en lecture du fichier
	std::ifstream ifs(pcGRAfileName, std::ifstream::in);
	try
	{
		//while (ifs.good())
		{
			ifs >> reader;
			if (strncmp(reader, "NBSommets=", 10) == 0)
			{
				char* pcGRAnbOfNodes = &reader[10];
				// verifications
				//atoi permet d'avoir une conversion char vers int.
				//Mais il y a des erreurs possible dans la conversion (ex: "123t56" --> "123" et "y123" --> "0"). 
				//On va donc tester si tous les char sont des entiers.
				if (CStringUtil::STUisAnInt(pcGRAnbOfNodes) == true)//si c'est bien un int...
				{
					int iGRAnbOfNodeOnFile = atoi(pcGRAnbOfNodes);// ... on le stock

					ifs >> reader;// lecture de la ligne suivante
					// de meme que la premiere ligne, on verifie les donnees
					if (strncmp(reader, "NBArcs=", 7) == 0)
					{
						char* pcGRAnbOfEdge = &reader[7];
						if (CStringUtil::STUisAnInt(pcGRAnbOfEdge) == true)//si c'est bien un int...
						{
							int iGRAnbOfEdgeOnFile = atoi(pcGRAnbOfEdge);// ... le stock ...
							ifs >> reader;// ... on debute la partie sur les noeuds
							if (strncmp(reader, "Sommets=[", 9) == 0)
							{
								// ... et on passe a la creation des noeuds :
								for (; iGRAnbOfNodeOnFile > 0; iGRAnbOfNodeOnFile--)// il y a iGRAnbOfNodeOnFile noeuds donc autant de lignes
								{
									ifs >> reader;//on lit la ligne ...
									if (strncmp(reader, "Numero=", 7) == 0)// ... on verifie que c'est bien un numero de noeud...
									{
										char* pcGRAidOfNode = &reader[7];
										if (CStringUtil::STUisAnInt(pcGRAidOfNode) == true)// ... si c'est bien un int ...
										{
											this->GRAaddNode(atoi(pcGRAidOfNode));// ... on cree le noeud dans le graph courant
										}
										else// sinon on leve une exception en mode erreur
										{
											ifs.close();
											Cexception EXCcontenuFichierNonValide("Error - CGraph constructor pcGRAfileName - number of nodes not valid");
											throw EXCcontenuFichierNonValide;
										}
									}
									else
									{
										Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s node not valid");
										throw EXCheaderNotValid;
									}
								}
								// arrive ici, on doit avoir une fin de partie de noeuds
								ifs >> reader;
								if (strncmp(reader, "]", 1) == 0)// on termine la partie sur les noeuds
								{
									ifs >> reader;// ... on debute la partie sur les arcs
									if (strncmp(reader, "Arcs=[", 6) == 0)
									{
										// ... et on passe a la creation des arcs :
										for (; iGRAnbOfEdgeOnFile > 0; iGRAnbOfEdgeOnFile--)// il y a iGRAnbOfEdgeOnFile arcs donc autant de lignes
										{
											int iIdOfDepartureNode;
											int ifOfArrivalNode;
											ifs >> reader;//on lit la ligne jusqu'a l'espace ...
											char pcBegin[7] = "Debut=";
											char pcEnd[5] = "End=";
											int iSizeOfReader = CStringUtil::STUgetLength(reader);
											if (strncmp(reader, pcBegin, 6) == 0 && reader[iSizeOfReader-1] == ',')// ... on verifie que c'est bien un debut d'arc et qu'il y a une virgule a la fin ...
											{
												reader[iSizeOfReader-1] = '\0';//on supprime la virgule
												char* pcGRAidOfNode = &reader[6];
												if (CStringUtil::STUisAnInt(pcGRAidOfNode) == true)// ... si c'est bien un int ...
												{
													iIdOfDepartureNode = atoi(pcGRAidOfNode);// ... on le stock pour l'utiliser plus tard
													ifs >> reader; // lecture de la fin de ligne
													if (strncmp(reader, "Fin=", 4) == 0)// ... on verifie que c'est bien une arrivee d'arc ...
													{
														char* pcGRAidOfNode = &reader[4];
														if (CStringUtil::STUisAnInt(pcGRAidOfNode) == true)// ... si c'est bien un int ...
														{
															ifOfArrivalNode = atoi(pcGRAidOfNode);
															this->GRAaddEdge(iIdOfDepartureNode, ifOfArrivalNode);// ... on cree l'arc dans le graph courant a l'aide des deux ID recuperes
														}
														else// sinon on leve une exception en mode erreur
														{
															ifs.close();
															Cexception EXCcontenuFichierNonValide("Error - CGraph constructor pcGRAfileName - endge\'s ending ID not valid");
															throw EXCcontenuFichierNonValide;
														}
													}
													else
													{
														Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s ending edge not valid");
														throw EXCheaderNotValid;
													}
													//this->GRAaddEdge(iIdOfDepartureNode, ifOfArrivalNode);// ... on cree le noeud dans le graph courant
												}
												else// sinon on leve une exception en mode erreur
												{
													ifs.close();
													Cexception EXCcontenuFichierNonValide("Error - CGraph constructor pcGRAfileName - number of nodes not valid");
													throw EXCcontenuFichierNonValide;
												}
											}
											else
											{
												Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s begining edge not valid");
												throw EXCheaderNotValid;
											}
										}
										// arrive ici, on doit avoir une fin de partie sur les arcs
										ifs >> reader;
										if (strncmp(reader, "]", 1) == 0)// on termine la partie sur les arcs
										{
											//on va tester si c'est bien la fin du fichier
											// si oui, on ferme le fichier
											// sinon on leve un warning et on ferme le fichier
										}
										else
										{
											Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s ending of edge part not valid");
											throw EXCheaderNotValid;
										}
									}
									else
									{
										Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s beginning of edge part not valid");
										throw EXCheaderNotValid;
									}
								}
								else
								{
									Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s ending of node part not valid");
									throw EXCheaderNotValid;
								}
							}
							else
							{
								Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s beginning of node part not valid");
								throw EXCheaderNotValid;
							}

							ifs.close();
						}
						else// sinon on leve une exception en mode erreur
						{
							ifs.close();
							Cexception EXCcontenuFichierNonValide("Error - CGraph constructor pcGRAfileName - number of edge not valid");
							throw EXCcontenuFichierNonValide;
						}
					}
					else
					{
						Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s edge header not valid");
						throw EXCheaderNotValid;
					}
				}
				else// sinon on leve une exception en mode erreur
				{
					ifs.close();
					Cexception EXCcontenuFichierNonValide("Error - CGraph constructor pcGRAfileName - number of nodes not valid");
					throw EXCcontenuFichierNonValide;
				}
			}
			else// sinon on leve une exception en mode erreur
			{
				Cexception EXCheaderNotValid("Error - CGraph constructor pcGRAfileName - file\'s node header not valid");
				throw EXCheaderNotValid;
			}
		}
	}
	catch (Cexception &e)
	{
		ifs.close();
		std::cout << e;
		exit(1);
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "Error - CGraph constructor pcGRAfileName - at openning/closing file" << std::endl;
		exit(1);
	}
}
/**
*	Entree : -
*	Necessite : ne pas avoir de pointeur sur un objet du graph
*	Sortie : -
*	Entraine : desallocation de la list de noeuds et destruction du graphe
*/
CGraph::~CGraph()
{
	int index;
	for (index = 0; index < iGRAnbOfNode; index++)
	{
		delete ppnGRAnodeList[index];
	}
	delete[] ppnGRAnodeList;
}
/**
*	Entree : l'ID du noeud a creer
*	Necessite : l'entree doit etre un ID libre sinon voir entraine
*	Sortie : un pointeur sur le noeud cree ou nullptr si il y a un probleme
*	Entraine :
*		creation d'un noeud d'ID idOfNode
*		OU (Cexception erreur en cas d'ID deja utilise ou erreur quelconque)
*/
CNode* CGraph::GRAaddNode(int idOfNode)
{
	try
	{
		if (GRAsearchNode(idOfNode) == nullptr)//si un noeud avec cet ID n'a pas deja etait defini dans ce graph
		{
			iGRAnbOfNode++;
			ppnGRAnodeList = (CNode**)realloc(ppnGRAnodeList, iGRAnbOfNode*sizeof(CNode*));
			if (ppnGRAnodeList == nullptr)
				throw Cexception("Error - GRAaddNode - realloc failure");

			ppnGRAnodeList[iGRAnbOfNode - 1] = new CNode(idOfNode);
			return ppnGRAnodeList[iGRAnbOfNode - 1];
		}
		Cexception EXCnodeAlreadyExists("Error - GRAaddNode - the ID of the node is already taken");
		throw EXCnodeAlreadyExists;
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree : l'ID du noeud a supprimer
*	Necessite : l'entree doit etre un ID utilise sinon voir entraine
*	Sortie : -
*	Entraine :
*		suppression du noeud d'ID idOfNode
*		OU (Cexception erreur)
*		OU (Cexception warning si le noeud n'existe pas dans le graph)
*/
void CGraph::GRAdelNode(int idOfNode)
{
	CNode* pNODnodeToDelete = GRAsearchNode(idOfNode);
	try
	{
		if (pNODnodeToDelete != nullptr)//si un noeud avec cet ID est bien present dans le graph...
		{
			//suppression des arcs qui partent du noeud a supprimer
			int index;
			for (index = pNODnodeToDelete->NODgetNbOfDepartureEdge()-1; index > -1; index--)//on parcours la liste des arcs en partance du noeud
			{
				GRAdeleteEdge(idOfNode, pNODnodeToDelete->NODgetDepartureEdge()[index]->EDGgetNodeDestination());
			}
			//suppression des arcs qui vont vers le noeud a supprimer
			for (index = pNODnodeToDelete->NODgetNbOfArrivalEdge() - 1; index > -1; index--)//on parcours la liste des arcs arrivants vers le noeud
			{
				GRAdeleteEdge(pNODnodeToDelete->NODgetArrivalEdge()[index]->EDGgetNodeDestination(), idOfNode);
			}
			// desalocation des donnees restantes qui se trouve dans le noeud
			*pNODnodeToDelete = *ppnGRAnodeList[iGRAnbOfNode - 1];
			iGRAnbOfNode--;
			ppnGRAnodeList = (CNode**)realloc(ppnGRAnodeList, iGRAnbOfNode*sizeof(CNode*));
			if (ppnGRAnodeList == nullptr)
				throw Cexception("Error - GRAdelNode - realloc failure");
		}
		else// sinon on leve une exeption 
		{
			Cexception EXCnodeDoesntExist("Warning - GRAdelNode - the node can\'t be delete because it doesn\'t exist", false);//c'est un warning donc on n'arrete pas le programme
			throw EXCnodeDoesntExist;
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
	}
}
/**	
 *	ex: graph1 avec deux noeuds 1 et 2
 *	std::cout << graph1;
 *	1
 *	2
 *	GRAaddEdge(2, 1);
 *	std::cout << graph1;
 *	1
 *	2
 *		->1
 *	Entree :
 *		@param departureNodeId l'ID du noeud dont va partir l'arc
 *		@param arrivalNodeId l'ID du noeud vers lequel va aller l'arc
 *	Necessite : l'entree doit etre un ID utilise sinon voir entraine
 *	Sortie : -
 *	Entraine :
 *		creation d'un arc entre deux noeuds
 *		OU (Cexception erreur si l'un des deux noeuds n'existe pas dans le graph)
 */
void CGraph::GRAaddEdge(int departureNodeId, int arrivalNodeId)
{
	try
	{
		CNode* pnNODdepartureNode = GRAsearchNode(departureNodeId);
		CNode* pnNODarrivalNode = GRAsearchNode(arrivalNodeId);
		if (pnNODdepartureNode != nullptr && pnNODarrivalNode != nullptr)// si les deux noeuds sont dans le graph
		{
			pnNODdepartureNode->NODaddDepartureEdge(arrivalNodeId);
			pnNODarrivalNode->NODaddArrivalEdge(departureNodeId);
		}
		else// sinon on leve une exception
		{
			Cexception EXCnodeDoesntExist("Error - GRAaddEdge - the edge can\'t be created because one of the node doesn\'t exist");
			throw EXCnodeDoesntExist;
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
	}
}
/**
*	Entree :
*		@param departureNodeId l'ID du noeud duquel part l'arc
*		@param arrivalNodeId l'ID du noeud vers lequel l'arc va
*		@param cTypeOfDel : 'a' ou rien pour supprimer tous les arcs sinon on supprime seulement le 1er arc trouve dans la liste
*	Necessite : l'entree doit etre un ID utilise sinon voir entraine
*	Sortie : -
*	Entraine :
*		suppression du noeud d'ID idOfNode
*		OU (Cexception warning si le noeud n'existe pas dans le graph)
*/
void CGraph::GRAdeleteEdge(int departureNodeId, int arrivalNodeId, char cTypeOfDel)
{
	try
	{
		CNode* pnNODdepartureNode = GRAsearchNode(departureNodeId);
		CNode* pnNODarrivalNode = GRAsearchNode(arrivalNodeId);
		if (pnNODdepartureNode != nullptr && pnNODarrivalNode != nullptr)
		{
			pnNODdepartureNode->NODdelDepartureEdge(arrivalNodeId);
			pnNODarrivalNode->NODdelArrivalEdge(departureNodeId);
		}
		else
		{
			Cexception EXCnodeDoesntExist("Warning - GRAdeleteEdge - the edge can\'t be deleted because one of the node doesn\'t exist", false);// est un warning donc le programme continue
			throw EXCnodeDoesntExist;
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
	}
}
/**
*	Entree : l'ID du noeud a chercher
*	Necessite : -
*	Sortie : un pointeur sur le noeud d'ID nodeIdToSearch
*		OU (un pointeur sur nullptr si le noeud n'est pas dans le graph)
*	Entraine : -
*/
CNode* CGraph::GRAsearchNode(int nodeIdToSearch)
{
	int iIndex;
	for (iIndex=0; iIndex < iGRAnbOfNode; iIndex++)
		if (GRAgetNodeList()[iIndex]->NODgetId() == nodeIdToSearch)
		{
			return GRAgetNodeList()[iIndex];
		}
	return nullptr;
}

/**
*	Entree : une reference sur un graph
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage du graph
*/
std::ostream &operator<<(std::ostream &OSTflux, CGraph &GRAparam)
{
	int iIndex = 0;
	for (; iIndex < GRAparam.EDGgetNbOfNode(); iIndex++)
	{
		std::cout << *GRAparam.GRAgetNodeList()[iIndex];
	}
	return std::cout;
}
