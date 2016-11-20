
#ifndef C_GRAPH_H
#define C_GRAPH_H

#include <fstream>
#include "Cexception.h"
#include "CNode.h"
#include "CEdge.h"
#include "CStringUtil.h"

class CGraph{
	private:
		int iGRAnbOfNode;
		CNode** ppnGRAnodeList;
		bool bGRAisDirected;
	public:
		/**
		*	Entree : -
		*	Necessite : ne pas etre utilise, l'utilisation normale est celle par le constructeur avec un fichier d'entree
		*	Sortie : -
		*	Entraine : creation d'un nouveau graph qui est vide et oriente
		*/
		CGraph();
		/**
		*	Entree : une chaine de caractere correspondant en nom du fichier dans lequel se trouve un graph
		*	Necessite : -
		*	Sortie : -
		*	Entraine : 
		*		creation d'un nouveau graph oriente ayant les valeurs du fichier
		*		OU (throw Cexception)
		*/
		CGraph(char* pcGRAfileName);
		/**
		*	Entree : -
		*	Necessite : ne pas avoir de pointeur sur un objet du graph
		*	Sortie : -
		*	Entraine : desallocation de la list de noeuds et destruction du graphe
		*/
		~CGraph();
		
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : le nombre de noeuds du graph
		*	Entraine : -
		*/
		int EDGgetNbOfNode(){ return iGRAnbOfNode; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : la liste des noeuds du graph
		*	Entraine : -
		*/
		CNode** GRAgetNodeList(){ return ppnGRAnodeList; }
		/**
		*	Entree : l'ID du noeud a creer
		*	Necessite : l'entree doit etre un ID libre sinon voir entraine
		*	Sortie : un pointeur sur le noeud cree ou nullptr si il y a un probleme
		*	Entraine :
		*		creation d'un noeud d'ID idOfNode
		*		OU (Cexception erreur en cas d'ID deja utilise ou erreur quelconque)
		*/
		CNode* GRAaddNode(int idOfNode);
		/**
		*	Entree : l'ID du noeud a supprimer
		*	Necessite : l'entree doit etre un ID utilise sinon voir entraine
		*	Sortie : -
		*	Entraine :
		*		suppression du noeud d'ID idOfNode
		*		OU (Cexception erreur)
		*		OU (Cexception warning si le noeud n'existe pas dans le graph)
		*/
		void GRAdelNode(int nodeIdToDelete);
		/**
		*	ex: graph1 avec deux noeuds 1 et 2
		*	std::cout << graph1;
		*	1
		*	2
		*	GRAaddEdge(2, 1);
		*	std::cout << graph1;
		*	1
		*	2
		*		->1
		*	Entree :
		*		@param departureNodeId l'ID du noeud dont va partir l'arc
		*		@param arrivalNodeId l'ID du noeud vers lequel va aller l'arc
		*	Necessite : l'entree doit etre un ID utilise sinon voir entraine
		*	Sortie : -
		*	Entraine :
		*		creation d'un arc entre deux noeuds
		*		OU (Cexception erreur si l'un des deux noeuds n'existe pas dans le graph)
		*/
		void GRAaddEdge(int departureNodeId, int arrivalNodeId);
		/**
		*	Entree : 
		*		@param departureNodeId l'ID du noeud duquel part l'arc
		*		@param arrivalNodeId l'ID du noeud vers lequel l'arc va
		*		@param cTypeOfDel : 'a' ou rien pour supprimer tous les arcs sinon on supprime seulement le 1er arc trouve dans la liste
		*	Necessite : l'entree doit etre un ID utilise sinon voir entraine
		*	Sortie : -
		*	Entraine :
		*		suppression du noeud d'ID idOfNode
		*		OU (Cexception warning si le noeud n'existe pas dans le graph)
		*/
		void GRAdeleteEdge(int departureNodeId, int arrivalNodeId, char cTypeOfDel='a');
		/**
		* Print the current graph
		* @example:
		* <node1>
		*	-> <destinationEdge1>
		*	-> <destinationEdge2>
		*	...
		*	-> <destinationEdge_n>
		* <node_n>
		*	...
		*
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : affichage du graph
		*/
		void GRAprintGraph(){ std::cout << this; }
		/**
		*	Entree : l'ID du noeud a chercher
		*	Necessite : -
		*	Sortie :
		*		@return un pointeur sur le noeud d'ID nodeIdToSearch
		*		@return OU (un pointeur sur nullptr si le noeud n'est pas dans le graph)
		*	Entraine : -
		*/
		CNode* GRAsearchNode(int nodeIdToSearch);
};

/**
*	Entree : une reference sur un graph
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage du graph
*/
std::ostream &operator<<(std::ostream &OSTflux, CGraph &GRAparam);

#endif
