#ifndef C_GRAPH_READER_H
#define C_GRAPH_READER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CGraph.h"

class CGraphReader
{
private:
	char* pcGRDfileName;

	CGraph cGraph;

public:
	/**
	 *  
	 *  
	 */
	CGraphReader(char* pcFileName);

	~CGraphReader();

	/**
	 *  
	 */
	boolean GRDisAnInt();

};
#endif
