
#include "CEdgeUtil.h"

/**
*	Entree :
*		@param GRAgraph reference sur le graph courant
*		@param iDepartureId l'ID du noeud pour lequel on fait un changement
*		@param iOldArrivalId l'ID du noeud sur lequel l'arc va avant le changement
*		@param iNewArrivalId l'ID du noeud sur lequel l'arc va apres le changement
*	Necessite : -
*	Sortie : -
*	Entraine : le changement de de destination de l'arc
*		OU (Cexception "l'un des noeud n'existe pas")
*/
void CEdgeUtil::EDUmodifyDestinationNode(CGraph &GRAgraph, int iDepartureId, int iOldArrivalId, int iNewArrivalId)
{
	CNode* pnNODdepartureNode = GRAgraph.GRAsearchNode(iDepartureId);
	CNode* pnNODoldArrivalNode = GRAgraph.GRAsearchNode(iOldArrivalId);
	CNode* pnNODnewArrivalNode = GRAgraph.GRAsearchNode(iNewArrivalId);
	if (pnNODdepartureNode != nullptr && pnNODoldArrivalNode != nullptr && pnNODnewArrivalNode != nullptr)//si 3 noeuds existent
	{
		//printf("fonction EDUmodifyDestinationNode - CEdgeUtil - non implementee");
		//TODO
		// supprimer arc de pnNODoldArrivalNode vers pnNODdepartureNode
		// setDestination arc pnNODdepartureNode->pnNODoldArrivalNode pour pnNODdepartureNode->pnNODnewArrivalNode
		// creer arc de pnNODnewArrivalNode vers pnNODdepartureNode
		
		pnNODoldArrivalNode->NODdelArrivalEdge(iDepartureId);
		CEdge* peEDGedgeToMChange = pnNODdepartureNode->NODsearchDepartureEdge(iOldArrivalId);
		peEDGedgeToMChange->EDGsetNodeDestination(iNewArrivalId);
		pnNODnewArrivalNode->NODaddArrivalEdge(iDepartureId);
		//pnNODdepartureNode->NODgetDepartureEdge();
	}
}

