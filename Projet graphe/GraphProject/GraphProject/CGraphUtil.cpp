#include "CGraphUtil.h"

/**
*	Entree : une reference sur un graph
*	Necessite : -
*	Sortie : -
*	Entraine : inverse tous le graph
*/
void CGraphUtil::GRUreverseGraph(CGraph &GRAparam)
{
	int iIndexOfNode;
	for (iIndexOfNode = 0; iIndexOfNode < GRAparam.EDGgetNbOfNode(); iIndexOfNode++)
	{
		CNodeUtil::NOUreverseNode(*GRAparam.GRAgetNodeList()[iIndexOfNode]);
	}
}
