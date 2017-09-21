#ifndef INTERFACECLASS_H_
#define INTERFACECLASS_H_

#include "configN.h"
#include "primaryFunctionalFunc.h"
#include "preambleFunc.h"
#include "DataSym.h"

class InterfaceClass
{
public:
	Vec_compA_3D txSignal;
	wlan_txparam txvector;
	InterfaceClass()
	{
	}
	~InterfaceClass()
	{
	}
	void DataGenerate( int DataLen,vector<int> src);
};

#endif