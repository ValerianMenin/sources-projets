
#ifndef C_GRAPH_UTIL_H
#define C_GRAPH_UTIL_H

#include "Cexception.h"
#include "CNodeUtil.h"
#include "CGraph.h"

class CGraphUtil
{
	public:
		/**
		*	Entree : une reference sur un graph
		*	Necessite : -
		*	Sortie : -
		*	Entraine : inverse tous le graph
		*/
		static void GRUreverseGraph(CGraph &GRAparam);
};

#endif
