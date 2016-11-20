
#include <iostream>
#include "Cexception.h"
#include "CEdge.h"
#include "CNode.h"
#include "CGraph.h"
#include "CEdgeUtil.h"
#include "CGraphUtil.h"
#include "CNodeUtil.h"
#include "CStringUtil.h"

void testEdge()
{
	CEdge edge1(2);

	std::cout << edge1;
	edge1.EDGsetNodeDestination(5);
	std::cout << edge1;
}
void testNode()
{

	CNode* cnode1 = new CNode();//"CNode* cnode1 = new CNode();" mais "CNode* cnode1();" ne fonctionne pas
	std::cout << *cnode1;

	CNode cnode2(2);
	CNode cnode3(3);
	CNode cnode4(4);
	CNode cnode5(5);
	CNode cnode6(6);
	CNode cnode7(7);
	CNode cnode8(8);

	cnode2.NODaddDepartureEdge(5);
	cnode2.NODaddDepartureEdge(5);
	cnode2.NODaddDepartureEdge(5);
	cnode2.NODaddDepartureEdge(1);
	cnode2.NODaddDepartureEdge(2);
	cnode2.NODaddDepartureEdge(2);
	cnode2.NODaddDepartureEdge(8);
	cnode2.NODaddDepartureEdge(8);
	cnode2.NODaddDepartureEdge(8);
	cnode2.NODaddDepartureEdge(8);
	cnode2.NODaddDepartureEdge(8);
	cnode2.NODaddDepartureEdge(10);
	std::cout << cnode2 << std::endl;

	cnode2.NODdelDepartureEdge(5);
	cnode2.NODdelDepartureEdge(8, 'o');

	std::cout << cnode2 << std::endl;


}
void testGraph()
{

	CNode cnode1 = CNode();
	CNode cnode2 = CNode();
	//std::cout << cnode1.NODgetiNODid() << std::endl << cnode2 << std::endl;

	CGraph cgraph1 = CGraph();

	CNode* cnode3 = cgraph1.GRAaddNode(3);
	CNode* cnode4 = cgraph1.GRAaddNode(4);
	CNode* cnode5 = cgraph1.GRAaddNode(5);
	CNode* cnode6 = cgraph1.GRAaddNode(6);
	cgraph1.GRAaddEdge(3, 4);
	std::cout << "cgraph1 with : 3, 4, 5, 6\nand Edge : 3->4" << std::endl << cgraph1 << std::endl;

	cgraph1.GRAaddEdge(3, 4);
	cgraph1.GRAaddEdge(4, 3);
	cgraph1.GRAaddEdge(4, 4);
	std::cout << "cgraph1 with Edge (3->4), (4->3), (4->4)" << std::endl << cgraph1 << std::endl;

	std::cout << *cgraph1.GRAsearchNode(3); std::cout << cgraph1.GRAsearchNode(3)->NODgetNbOfDepartureEdge(); std::cout << cgraph1.GRAsearchNode(3)->NODgetNbOfArrivalEdge();
	cgraph1.GRAdelNode(3);
	std::cout << "cgraph1 with : del 3" << std::endl << cgraph1 << std::endl;

	cgraph1.GRAdelNode(3);
	std::cout << "cgraph1 with : del 3" << std::endl << cgraph1 << std::endl;

}
void testGraphFile(char* pcparam)
{
	CGraph graph2(pcparam);
	std::cout << graph2;
}

int main(int argc, char* argv[])
{
	//testEdge();
	//testNode();
	//testGraph();
	//testGraphFile("fichier1.txt");

	int iIndexOfArg;
	for (iIndexOfArg = 1; iIndexOfArg < argc; iIndexOfArg++)
	{
		CGraph graph1(argv[iIndexOfArg]);
		std::cout << "original graph\n" << graph1 << "\n";
		//CEdgeUtil::EDUmodifyDestinationNode(graph1, 1, 2, 3);
		//std::cout << "EDUmodifyDestinationNode(graph1, 1, 2, 3)\n" << graph1 << "\n";
		//CNodeUtil::NOUmodifyNodeId(graph1, 3, 4);
		//std::cout << "NOUmodifyNodeId(graph1, 3, 4)\n" << graph1;
		CGraphUtil::GRUreverseGraph(graph1);
		std::cout << "GRUreverseGraph(graph1)\n" << graph1;


		//Graph graph2(GRUreverse(*graph1));
		//std::cout << graph2;
	}

	return 0;
}
