#ifndef C_EDGE_H
#define C_EDGE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CGraph.h"
#include "CNode.h"
#include "ostream.h"

class CEdge
{
private:
	int iEDGnodeDestination;

	CGraph cGraph;
	CNode cNode;
	CNode cNode;

public:
	CEdge();

	/**
	 *  
	 */
	CEdge(int iNodeDestination);

	~CEdge();

	void EDGsetnodDestination(int iEDGparam);

	int EDGgetiEDGnodeDestination();

	ostream &operator<<(ostream &OSTflux, CEdge &EDGparam);

};
#endif
