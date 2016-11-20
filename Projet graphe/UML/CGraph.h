#ifndef C_GRAPH_H
#define C_GRAPH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CNode.h"
#include "CEdge.h"
#include "CGraphReader.h"
#include "ostream.h"

class CGraph
{
private:
	CNode** ppnGRAnodeList;

	CNode cNode[];
	CEdge cEdge;
	CGraphReader cGraphReader;

public:
	/**
	 *  
	 *  
	 */
	CGraph(int iNumberOfNodes);

	~CGraph();

	void GRAsetNodeList(CNode** ppnGRAparam);

	CNode** GRAgetppnGRAnodeList();

	/**
	 *  
	 */
	void GRAaddNode();

	void GRAdeleteNode(int nodeIdToDelete);

	/**
	 *  
	 */
	void GRAaddEdge(int departureNodeId, int arrivalNodeId);

	/**
	 *  
	 */
	void GRAdeleteEdge(int departureNodeId, int arrivalNodeId);

	/**
	 *  
	 */
	void GRAprintGraph();

	CNode* GRAsearchNode(int nodeIdToSearch);

	ostream &operator<<(ostream &OSTflux, CGraph &GRAparam);

};
#endif
