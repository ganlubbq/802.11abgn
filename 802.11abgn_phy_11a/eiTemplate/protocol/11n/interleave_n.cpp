#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "primaryFunctionalFunc.h"

int* interleave_n(int* dataIn, int modType, int format, int MCS, int BW, int iss, int Nbpscs)
{
	//IlvTypes 1 = 20 M legacy, 2 = 20 MHz HT, 3 = 40 MHz HT
	int NsdPerBwtype[] = { 48, 52, 108 };
	int Ncbpss = NsdPerBwtype[modType-1] * Nbpscs;

	int Ncol,Nrow,Nrot;
	vector<int> k;
	for(int i=0;i<Ncbpss;++i)
		k.push_back(i);
	vector<int> firstStepIndex(Ncbpss);
	vector<int> secondStepIndex(Ncbpss);
	vector<int> thirdStepIndex(Ncbpss);

	int s = (Nbpscs/2<1)?1:Nbpscs/2;

	int* dataInterleaved = new int [Ncbpss];
	int* dataTemp1 = new int [Ncbpss];
	int* dataTemp2 = new int [Ncbpss];

	if(format == Legacy || MCS == 32)
	{
		// First permutation	
		for(int i=0;i<Ncbpss;++i)
		{
			firstStepIndex[i] = (Ncbpss/16)*(k[i]%16) + k[i]/16;
			dataTemp1[firstStepIndex[i]] = dataIn[i];
		}
		//Second permutation
		for(int i=0;i<Ncbpss;++i)
		{
			secondStepIndex[i] = s*(k[i]/s) + (k[i]+Ncbpss-16*k[i]/Ncbpss)%s;
			dataInterleaved[secondStepIndex[i]] = dataTemp1[i];
		}
	}
	else
	{
		switch (BW)
		{
		case 0://20M
		case 10:
			Ncol = 13;
			Nrow = 4*Nbpscs;
			Nrot = 11;
			break;
		case 1://40M
		case 11:
			Ncol = 18;
			Nrow = 6*Nbpscs;
			Nrot = 29;
			break;
		}
		//First permutation
		for(int i=0;i<Ncbpss;++i)
		{
			firstStepIndex[i] = Nrow*(k[i]%Ncol) + k[i]/Ncol;
			dataTemp1[firstStepIndex[i]] = dataIn[i];
		}
		//Second permutation
		for(int i=0;i<Ncbpss;++i)
		{
			secondStepIndex[i] = s*(k[i]/s) + (k[i]+Ncbpss-Ncol*k[i]/Ncbpss)%s;
			dataTemp2[secondStepIndex[i]] = dataTemp1[i];
		}
		//If Nss>1, a third permutation is needed
		for(int i=0;i<Ncbpss;++i)
		{
			thirdStepIndex[i] = (k[i]-((iss)*2%3 + 3*((iss)/3))*Nrot*Nbpscs) % Ncbpss;
			if(thirdStepIndex[i]<0)
				thirdStepIndex[i] += Ncbpss;
			dataInterleaved[thirdStepIndex[i]] = dataTemp2[i];
		}
	}
	return dataInterleaved;
}