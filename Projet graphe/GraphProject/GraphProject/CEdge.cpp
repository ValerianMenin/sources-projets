
#include "CEdge.h"

/**
*	Entree : une reference sur un arc
*	Necessite : -
*	Sortie : un flux
*	Entraine : affichage de l'arc "	-> <idDuNoeudDeDestination>"
*/
std::ostream &operator<<(std::ostream & OSTflux, CEdge &EDGparam)
{
	std::cout << "\t-> " << EDGparam.EDGgetNodeDestination() << std::endl;
	return std::cout;
}
