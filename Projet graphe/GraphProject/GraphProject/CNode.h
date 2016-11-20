
#ifndef C_NODE_H
#define C_NODE_H

#include "Cexception.h"
#include "CEdge.h"

class CNode
{
	private:
		int iNODid;
		int iNODnbOfDepartureEdge;
		int iNODnbOfArrivalEdge;
		CEdge** ppeNODdepartureEdge;
		CEdge** ppeNODarrivalEdge;

	public:
		/**
		*	Entree : -
		*	Necessite : ne pas etre utilise
		*	Sortie : -
		*	Entraine : creation d'un nouveau noeud
		*/
		CNode();
		/**
		*	Entree : l'ID du nouveau noeud
		*	Necessite : l'ID doit etre disponible
		*	Sortie : -
		*	Entraine : creation d'un nouveau noeud d'iNODid = -1
		*/
		CNode(int ID);
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : destruction du noeud par desaloccation des deux tableaux de CEdge puis destruction des 3 int
		*/
		~CNode();

		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : destruction du noeud
		*/
		int NODgetId(){ return iNODid; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : le nombre d'arcs partants du noeud
		*	Entraine : -
		*/
		int NODgetNbOfDepartureEdge(){ return iNODnbOfDepartureEdge; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : la tableau de pointeur sur les arcs partants
		*	Entraine : -
		*/
		CEdge** NODgetDepartureEdge(){ return ppeNODdepartureEdge; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : le nombre d'arcs arrivant au noeud
		*	Entraine : -
		*/
		int NODgetNbOfArrivalEdge(){ return iNODnbOfArrivalEdge; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : la tableau de pointeur sur les arcs arrivants
		*	Entraine : -
		*/
		CEdge** NODgetArrivalEdge(){ return ppeNODarrivalEdge; }
		/**
		*	Entree : un entier
		*	Necessite : doit seulement etre appele a partir de la fonction CNodeUtil::NOUreverseNode (c'est la seule a pouvoir resize en gardant l'integrite des donnees)
		*	Sortie : -
		*	Entraine : iNODnbOfDepartureEdge est modifie. Faux si la la fonction n'est pas appelee par CNodeUtil::NOUreverseNode
		*/
		void NODsetNbOfDepartureEdge(int iNbOfDepartureEdge){ iNODnbOfDepartureEdge = iNbOfDepartureEdge; }
		/**
		*	Entree : un entier
		*	Necessite : doit seulement etre appele a partir de la fonction CNodeUtil::NOUreverseNode (c'est la seule a pouvoir resize en gardant l'integrite des donnees)
		*	Sortie : -
		*	Entraine : iNODnbOfArrivalEdge est modifie. Faux si la la fonction n'est pas appelee par CNodeUtil::NOUreverseNode
		*/
		void NODsetNbOfArrivalEdge(int iNbOfArrivalEdge){ iNODnbOfArrivalEdge = iNbOfArrivalEdge; }
		/**
		*	Entree : un tableau de pointeurs sur des arcs
		*	Necessite : le tableau doit etre valide (les ID de destinations doivent etre dans le graph)
		*	Sortie : -
		*	Entraine : le tableau des arcs de depart est change
		*/
		void NODsetDepartureEdge(CEdge** ppeNODparam){ ppeNODdepartureEdge = ppeNODparam; }
		/**
		*	Entree : un tableau de pointeurs sur des arcs
		*	Necessite : le tableau doit etre valide (les ID de predecesseurs doivent etre dans le graph)
		*	Sortie : -
		*	Entraine : le tableau des arcs arrivant est change
		*/
		void NODsetArrivalEdge(CEdge** ppeNODparam){ ppeNODarrivalEdge = ppeNODparam; }

		/**
		*	Entree : l'ID du noeud vers lequel le nouveau arc va
		*	Necessite : idOfNode doit etre un ID d'un noeud du graph ne doit pas etre appele si le noeud est dans un graph car la liaison reciproque ne sera pas faite
		*	Sortie : -
		*	Entraine : ajoute un nouvel arc vers le noeud d'ID iNODidOfNode
		*		OU (throw Cexception)
		*/
		void NODaddDepartureEdge(int iNODidOfNode);
		/**
		*	Entree :
		*		@param iNODidOfNode : l'ID du noeud donc l'arc est a supprimer
		*		@param le mode de suppression 'a' pour "all" si l'on desire supprimer tous les arcs (si il y a plusieurs arcs allant vers ce noeud) pour un autre char, on en supprime un seul
		*	Necessite : la liaison doit etre supprimee dans l'autre sens
		*	Sortie : -
		*	Entraine :
		*		supprime un OU tous les arc(s) du noeud d'ID iNODidOfNode dans la liste des partants
		*		OU ne fait rien si l'arc n'est pas trouve
		*		OU (throw Cexception)
		*/
		void NODdelDepartureEdge(int iNODidOfNode, char ctypeOfDel='a');

		/**
		*	Entree : l'ID du noeud duquel l'arc vient
		*	Necessite : idOfNode doit etre un ID d'un noeud du graph ne doit pas etre appele si le noeud est dans un graph car la liaison reciproque ne sera pas faite
		*	Sortie : -
		*	Entraine : ajoute un nouvel element a la liste des noeuds arrivants
		*		OU (throw Cexception)
		*/
		void NODaddArrivalEdge(int iNODidOfNode);
		/**
		*	Entree :
		*		@param iNODidOfNode : l'ID du noeud donc l'arc est a supprimer
		*		@param le mode de suppression 'a' pour "all" si l'on desire supprimer tous les arcs (si il y a plusieurs arcs venants de ce noeud) pour un autre char, on en supprime un seul
		*	Necessite : la liaison doit etre supprimee dans l'autre sens
		*	Sortie : -
		*	Entraine :
		*		supprime un OU tous les arc(s) du noeud d'ID iNODidOfNode dans la liste des entrants
		*		OU ne fait rien si l'arc n'est pas trouve
		*		OU (throw Cexception)
		*/
		void NODdelArrivalEdge(int iNODidOfNode, char ctypeOfDel='a');

		/**
		*	Entree : l'ID du noeud vers lequel l'arc va
		*	Necessite : only find the first occurence
		*	Sortie :
		*		@return un pointeur sur l'arc donc l'ID du noeud est nodeIdToSearch
		*		@return OU (un pointeur sur nullptr si l'arc n'est pas dans le noeud)
		*	Entraine : -
		*/
		CEdge* NODsearchDepartureEdge(int iNODidOfNode);
		/**
		*	Entree : l'ID du noeud duquel l'arc vient
		*	Necessite : only find the first occurence
		*	Sortie :
		*		@return un pointeur sur l'arc donc l'ID du noeud est nodeIdToSearch
		*		@return OU (un pointeur sur nullptr si l'arc n'est pas dans le noeud)
		*	Entraine : -
		*/
		CEdge* NODsearchArrivalEdge(int iNODidOfNode);

};

/**
*	Entree : une reference sur un noeud
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage du noeud
*/
std::ostream &operator<<(std::ostream &OSTflux, CNode &NODparam);

#endif
