
#ifndef C_EDGE_UTIL_H
#define C_EDGE_UTIL_H

#include "Cexception.h"
#include "CGraph.h"
#include "CEdge.h"

class CEdgeUtil
{
	public:
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
		static void EDUmodifyDestinationNode(CGraph & GRAgraph, int iDepartureId, int iOldArrivalId, int iNewArrivalId);
};

#endif