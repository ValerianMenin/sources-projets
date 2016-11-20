
#ifndef C_EDGE_H
#define C_EDGE_H

#include "Cexception.h"
#include <iostream>

class CEdge{
	private:
		int iEDGnodeDestination;

	public:
		/**
		*	Entree : -
		*	Necessite : ne pas etre utilise
		*	Sortie : -
		*	Entraine : creation d'un nouvel arc qui va vers le noeud d'ID -1 (meme si il n'existe pas)
		*/
		CEdge(){ iEDGnodeDestination = -1;  }
		/**
		*	Entree : l'ID du noeud de destination
		*	Necessite : l'ID du noeud doit etre valide et appartenir au meme graph
		*	Sortie : -
		*	Entraine : creation d'un nouvel arc
		*/
		CEdge(int iNodeDestination){ iEDGnodeDestination = iNodeDestination; }
		/**
		*	Entree : l'arc a recopier
		*	Necessite : -
		*	Sortie : -
		*	Entraine : creation d'un nouvel arc identique a celui entre en parametre
		*/
		CEdge(CEdge &eEDGparam){ iEDGnodeDestination = eEDGparam.EDGgetNodeDestination(); }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : -
		*	Entraine : destruction de l'arc
		*/
		~CEdge(){}
		/**
		*	Entree : l'ID du noeud de la nouvelle destination
		*	Necessite : le noeud existe
		*	Sortie : -
		*	Entraine : le changement de de destination de l'arc
		*/
		void EDGsetNodeDestination(int iEDGparam){ iEDGnodeDestination = iEDGparam; }
		/**
		*	Entree : -
		*	Necessite : -
		*	Sortie : l'ID du noeud de destination
		*	Entraine : -
		*/
		int EDGgetNodeDestination(){ return iEDGnodeDestination; }
};

/**
*	Entree : une reference sur un arc
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage de l'arc "	-> <idDuNoeudDeDestination>"
*/
std::ostream &operator<<(std::ostream & OSTflux, CEdge &EDGparam);

#endif
