
#ifndef C_NODE_UTIL_H
#define C_NODE_UTIL_H

#include "Cexception.h"
#include "CGraph.h"
#include "CNode.h"

class CNodeUtil
{
public:
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : -
	*	Entraine : -
	*/
	CNodeUtil(){}
	/**
	*	Entree : -
	*	Necessite : -
	*	Sortie : -
	*	Entraine : -
	*/
	~CNodeUtil(){}

	/**
	*	Entree : une reference sur un graph, deux entiers
	*	Necessite : -
	*	Sortie : -
	*	Entraine : modifie tous les arcs partants et venants du noeud pour avoir le bon ID
	*/
	static void NOUmodifyNodeId(CGraph &GRAparam, int iOldId, int iNewId);
	/**
	*	Entree : une reference sur un noeud
	*	Necessite : -
	*	Sortie : -
	*	Entraine : inverse tous les arcs d'un noeud
	*/
	static void NOUreverseNode(CNode &NODparam);
};

#endif