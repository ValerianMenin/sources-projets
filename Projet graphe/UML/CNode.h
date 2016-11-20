#ifndef C_NODE_H
#define C_NODE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CEdge.h"
#include "CGraph.h"
#include "ostream.h"

class CNode
{
private:
	static int iNODlastIdUsed;
	int iNODid;
	CEdge** ppeNODdepartureEdge;
	CEdge** ppeNODarrivalEdge;
	CGraph cGraph;
	CEdge cEdge;
	CEdge cEdge;

public:
	/**
	 *  
	 */
	CNode();
	~CNode();
	int NODgetiNODid();
	void NODsetDepartureEdge(CEdge** ppeNODparam);
	CEdge** NODgetppeNODdepartureEdge();
	void NODsetarrivalEdge(CEdge** ppeNODparam);
	CEdge** NODgetppeNODarrivalEdge();
	ostream &operator<<(ostream &OSTflux, CNode &NODparam);

};
#endif
