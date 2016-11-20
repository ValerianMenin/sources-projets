#ifndef CEXCEPTION _H
#define CEXCEPTION _H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "ostream.h"
#include "CException.h"

class Cexception 
{
private:
	char* pcEXCvalue;


public:
	CException();

	/**
	 *  
	 */
	CException(char* pcEXCparam);

	~CException();

	void EXCsetpcEXCvalue(char* pcEXCparam);

	char* EXCgetpcEXCvalue();

	ostream ostream &operator<<(ostream &OSTflux, CException &EXCparam);

};
#endif
