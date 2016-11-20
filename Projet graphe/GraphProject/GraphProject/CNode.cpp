
#include "CNode.h"

/**
*	Entree : -
*	Necessite : ne pas etre utilise
*	Sortie : -
*	Entraine : creation d'un nouveau noeud
*/
CNode::CNode()
{
	iNODid = -1;
	iNODnbOfDepartureEdge = 0;
	iNODnbOfArrivalEdge = 0;
	ppeNODdepartureEdge = nullptr;
	ppeNODarrivalEdge = nullptr;
}
/**
*	Entree : l'ID du nouveau noeud
*	Necessite : l'ID doit etre disponible
*	Sortie : -
*	Entraine : creation d'un nouveau noeud d'iNODid = -1
*/
CNode::CNode(int ID)
{
	iNODid = ID;
	iNODnbOfDepartureEdge = 0;
	iNODnbOfArrivalEdge = 0;
	ppeNODdepartureEdge = nullptr;
	ppeNODarrivalEdge = nullptr;
}
/**
*	Entree : -
*	Necessite : -
*	Sortie : -
*	Entraine : destruction du noeud par desaloccation des deux tableaux de CEdge puis destruction des 3 int
*/
CNode::~CNode()
{
	int index;
	for (index = 0; index < iNODnbOfDepartureEdge; index++)
	{
		delete ppeNODdepartureEdge[index];
	}
	delete[] ppeNODdepartureEdge;
	for (index = 0; index < iNODnbOfArrivalEdge; index++)
	{
		delete ppeNODarrivalEdge[index];
	}
	delete[] ppeNODarrivalEdge;
}

/**
*	Entree : l'ID du noeud vers lequel le nouveau arc va
*	Necessite : idOfNode doit etre un ID d'un noeud du graph ne doit pas etre appele si le noeud est dans un graph car la liaison reciproque ne sera pas faite
*	Sortie : -
*	Entraine : ajoute un nouvel arc vers le noeud d'ID iNODidOfNode
*		OU (throw Cexception)
*/
void CNode::NODaddDepartureEdge(int idOfNode)
{
	try
	{
		iNODnbOfDepartureEdge++;
		ppeNODdepartureEdge = (CEdge**)realloc(ppeNODdepartureEdge, iNODnbOfDepartureEdge*sizeof(CEdge*));
		if (ppeNODdepartureEdge == nullptr)
			throw Cexception("Error - NODaddDepartureEdge - realloc failure");

		ppeNODdepartureEdge[iNODnbOfDepartureEdge - 1] = new CEdge(idOfNode);
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree : l'ID du noeud vers duquel l'arc vient
*	Necessite : idOfNode doit etre un ID d'un noeud du graph ne doit pas etre appele si le noeud est dans un graph car la liaison reciproque ne sera pas faite
*	Sortie : -
*	Entraine : ajoute un nouvel element a la liste des noeuds arrivants
*		OU (throw Cexception)
*/
void CNode::NODaddArrivalEdge(int idOfNode)
{
	try
	{
		iNODnbOfArrivalEdge++;
		ppeNODarrivalEdge = (CEdge**)realloc(ppeNODarrivalEdge, iNODnbOfArrivalEdge*sizeof(CEdge*));
		if (ppeNODarrivalEdge == nullptr)
			throw Cexception("Error - NODaddDepartureEdge - realloc failure");

		ppeNODarrivalEdge[iNODnbOfArrivalEdge - 1] = new CEdge(idOfNode);
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree :
*		@param iNODidOfNode : l'ID du noeud donc l'arc est a supprimer
*		@param le mode de suppression 'a' pour "all" si l'on desire supprimer tous les arcs (si il y a plusieurs arcs allant vers ce noeud) pour un autre char, on en supprime un seul
*	Necessite : la liaison doit etre supprimee dans l'autre sens
*	Sortie : -
*	Entraine : 
*		supprime un OU tous les arc(s) du noeud d'ID iNODidOfNode dans la liste des partants
*		OU ne fait rien si l'arc n'est pas trouve
*		OU (throw Cexception)
*/
void CNode::NODdelDepartureEdge(int iNODidOfNode, char ctypeOfDel)
{
	try
	{
		int index;
		for (index = 0; index < iNODnbOfDepartureEdge; index++)
		{
			//std::cout << "ppeNODdepartureEdge[index]->EDGgetNodeDestination()=" << ppeNODdepartureEdge[index]->EDGgetNodeDestination() << "\n";
			if (ppeNODdepartureEdge[index]->EDGgetNodeDestination() == iNODidOfNode) // si on a trouve le bon noeud
			{
				ppeNODdepartureEdge[index]->EDGsetNodeDestination(ppeNODdepartureEdge[iNODnbOfDepartureEdge - 1]->EDGgetNodeDestination());// on recopie le dernier element de la liste dans la partie a supprimer (le traitement du realloc est plus simple comme ca et on evite de tout decaler d'une case)
				iNODnbOfDepartureEdge--;
				ppeNODdepartureEdge = (CEdge**)realloc(ppeNODdepartureEdge, iNODnbOfDepartureEdge*sizeof(CEdge*));
				if (ppeNODdepartureEdge == nullptr && iNODnbOfDepartureEdge!=0)
					throw Cexception("Error - NODdelDepartureEdge - realloc failure");
				if (ctypeOfDel != 'a')
					index = iNODnbOfDepartureEdge; // cette etape permet de NE PAS supprimer tous les arcs (au cas ou il y aurrait plusieurs arc partants vers le meme noeud)
			}
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree :
*		@param iNODidOfNode : l'ID du noeud donc l'arc est a supprimer
*		@param le mode de suppression 'a' pour "all" si l'on desire supprimer tous les arcs (si il y a plusieurs arcs venants de ce noeud) pour un autre char, on en supprime un seul
*	Necessite : la liaison doit etre supprimee dans l'autre sens
*	Sortie : -
*	Entraine : 
*		supprime un OU tous les arc(s) du noeud d'ID iNODidOfNode dans la liste des entrants
*		OU ne fait rien si l'arc n'est pas trouve
*		OU (throw Cexception)
*/
void CNode::NODdelArrivalEdge(int iNODidOfNode, char ctypeOfDel)
{
	try
	{
		int index;
		for (index = 0; index < this->iNODnbOfArrivalEdge; index++)
		{
			if (ppeNODarrivalEdge[index]->EDGgetNodeDestination() == iNODidOfNode) // si on a trouve le bon noeud
			{
				ppeNODarrivalEdge[index]->EDGsetNodeDestination(ppeNODarrivalEdge[this->iNODnbOfArrivalEdge - 1]->EDGgetNodeDestination());// on recopie le dernier element de la liste dans la partie a supprimer (le traitement du realloc est plus simple comme ca et on evite de tout decaler d'une case)
				this->iNODnbOfArrivalEdge--;
				ppeNODarrivalEdge = (CEdge**)realloc(ppeNODarrivalEdge, this->iNODnbOfArrivalEdge*sizeof(CEdge*));
				if (ppeNODarrivalEdge == nullptr && iNODnbOfArrivalEdge!=0)
					throw Cexception("Error - CNode NODdelArrivalEdge - realloc failure");
				if (ctypeOfDel != 'a')
					index = iNODnbOfArrivalEdge; // cette etape permet de NE PAS supprimer tous les arcs (au cas ou il y aurrait plusieurs arc arrivants du meme noeud)
			}
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree : l'ID du noeud vers lequel l'arc va
*	Necessite : only find the first occurence
*	Sortie :
*		@return un pointeur sur l'arc donc l'ID du noeud est nodeIdToSearch
*		@return OU (un pointeur sur nullptr si l'arc n'est pas dans le noeud)
*	Entraine : -
*/
CEdge* CNode::NODsearchDepartureEdge(int iNODidOfNode)
{
	int index;
	for (index = 0; index < iNODnbOfDepartureEdge; index++)
	{
		if (ppeNODdepartureEdge[index]->EDGgetNodeDestination() == iNODidOfNode) // si on a trouve le bon noeud
		{
			return ppeNODdepartureEdge[index];
		}
	}
	return nullptr;
}
/**
*	Entree : l'ID du noeud duquel l'arc vient
*	Necessite : only find the first occurence
*	Sortie :
*		@return un pointeur sur l'arc donc l'ID du noeud est nodeIdToSearch
*		@return OU (un pointeur sur nullptr si l'arc n'est pas dans le noeud)
*	Entraine : -
*/
CEdge* CNode::NODsearchArrivalEdge(int iNODidOfNode)
{
	int index;
	for (index = 0; index < iNODnbOfArrivalEdge; index++)
	{
		if (ppeNODarrivalEdge[index]->EDGgetNodeDestination() == iNODidOfNode) // si on a trouve le bon noeud
		{
			return ppeNODarrivalEdge[index];
		}
	}
	return nullptr;
}

/**
*	Entree : une reference sur un noeud
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage du noeud
*/
std::ostream &operator<<(std::ostream &OSTflux, CNode &NODparam)
{
	std::cout << NODparam.NODgetId() << std::endl;
	int iIndex;
	for (iIndex = 0; iIndex < NODparam.NODgetNbOfDepartureEdge(); iIndex++)
	{
		std::cout << *NODparam.NODgetDepartureEdge()[iIndex];
	}
	return std::cout;
}
