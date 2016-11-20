#ifndef C_LEC
#define C_LEC
#pragma once
#include <stdio.h>
#include <fstream> //std::ifstream
#include "Cexception.h"
#include "CMatrice.h"

// type CLecteurMatrice : t
// type CMatrice        : q
class CLecteurMatrice
{
	private:
		char* pcLECnomFichier;
		CMatrice<double> MATmatrice;

	public:
		CLecteurMatrice(){}
		CLecteurMatrice(char* pcLECparam, CMatrice<double> MATparam);
		CLecteurMatrice(CLecteurMatrice  & LECparam){ cout << "1\n"; pcLECnomFichier = LECparam.pcLEClireNomFichier(); cout << "2"; cout << "3\n"; MATmatrice = LECparam.qLEClireMatrice(); cout << "4\n"; }
		~CLecteurMatrice(){}

		char* pcLEClireNomFichier(){ return pcLECnomFichier; }
		CMatrice<double> qLEClireMatrice(){ return MATmatrice; }
		void LECmodifierNomFichier(char* pcLECnouveauNomFichier){ pcLECnomFichier = pcLECnouveauNomFichier; }
		
};

CMatrice<double> qLECLectureFichierMatrice(char* pcLECnomFichier);
CMatrice<double> qLECcreateurMatriceCourante(char* pcLECparam);
bool bLECestUnDouble(char* pcparam);

#endif
