
#include "CNodeUtil.h"

/**
*	Entree : une reference sur un graph, deux entiers
*	Necessite : -
*	Sortie : -
*	Entraine : modifie tous les arcs partants et venants du noeud pour avoir le bon ID
*/
void CNodeUtil::NOUmodifyNodeId(CGraph &GRAparam, int iOldId, int iNewId)
{
	CNode* pnNODoldNode = GRAparam.GRAsearchNode(iOldId);
	CNode* pnNODnewNode = GRAparam.GRAsearchNode(iNewId);
	try
	{
		if (pnNODoldNode != nullptr)//si l'ID de l'ancien noeud existe
		{
			if (pnNODnewNode == nullptr)// si le nouvel ID du noeud n'existe pas, on le cree
			{
				GRAparam.GRAaddNode(iNewId);
				pnNODnewNode = GRAparam.GRAsearchNode(iNewId);
			}
			int iCurrentId;
			while (pnNODoldNode->NODgetNbOfDepartureEdge() > 0)// tant qu'il y a des arcs dans la liste des partants
			{
				iCurrentId = pnNODoldNode->NODgetDepartureEdge()[0]->EDGgetNodeDestination();
				GRAparam.GRAaddEdge(iNewId, iCurrentId);// creation d'un arc
				GRAparam.GRAdeleteEdge(iOldId, iCurrentId);// suppression du premier arc en partance de l'ancien noeud
			}
			while (pnNODoldNode->NODgetNbOfArrivalEdge() > 0)// tant qu'il y a des arcs dans la liste des arrivants
			{
				iCurrentId = pnNODoldNode->NODgetArrivalEdge()[0]->EDGgetNodeDestination();
				GRAparam.GRAaddEdge(iCurrentId, iNewId);// creation d'un arc
				GRAparam.GRAdeleteEdge(iCurrentId, iOldId);// suppression du premier arc en provenance de l'ancien noeud
			}
			// ici, il n'y a plus rien dans l'ancien CNode, tout a etait copier dans le nouveau CNode
			pnNODoldNode = pnNODnewNode;//changement de pointeur
			GRAparam.GRAdelNode(iOldId);//destruction de l'ancien noeud
		}
		else//sinon on leve une exception en mode erreur
		{
			Cexception EXCnodeDoesntExist("Error - NOUmodifyNodeId - the old node can\'t be modified because it doesn\'t exist");// est un warning donc le programme continue
			throw EXCnodeDoesntExist;
		}
	}
	catch (Cexception e)
	{
		std::cerr << e;
		exit(1);
	}
}
/**
*	Entree : une reference sur un noeud
*	Necessite : -
*	Sortie : -
*	Entraine : inverse tous les arcs d'un noeud
*/
void CNodeUtil::NOUreverseNode(CNode &NODparam)
{
	CEdge** ppeEDGtempoArrival = NODparam.NODgetArrivalEdge();// une temporisation
	int iNbOfArrivalEdge = NODparam.NODgetNbOfArrivalEdge();
	NODparam.NODsetArrivalEdge(NODparam.NODgetDepartureEdge());//recopie
	NODparam.NODsetNbOfArrivalEdge(NODparam.NODgetNbOfDepartureEdge());
	NODparam.NODsetDepartureEdge(ppeEDGtempoArrival);//fin de l'echange
	NODparam.NODsetNbOfDepartureEdge(iNbOfArrivalEdge);
}

