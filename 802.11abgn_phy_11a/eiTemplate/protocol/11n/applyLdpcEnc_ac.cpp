/*----------------------------------------------------
 Function Description: LDPC encoder core
---------------------------------------------------
History:
Created by hxy   Date:2014-12-1    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
        bitIn    : uncoded binary input: [service_field, data]
		ldpcPara : LDPC parameters
		cwIdx    : codeword index, for iterative detection and decode
----------------------------------------------------
Output Parameters:
           pktEncOut : coded bits
		   Nsym      : 
---------------------------------------------------*/
#include "stdafx.h"
#include <cstdarg>
#include <stdio.h>
#include "ldpc_encode.h"

using namespace std;

applyLdpcEnc_out applyLdpcEnc_ac(int *bitIn,ldpcPara out_str,int cwIdx)
{
	int Ncw,K0,Nsym;
    int Npunc;        
	int idxCwLen,idxRate;
	// the following vectors are 1-by-Ncw
	int *vNshrt=NULL,*vNpunc=NULL,*vNrepInt=NULL,*vNrepRem=NULL;
		
	Ncw = out_str.Ncw;
	Nsym = out_str.Nsym;
    Npunc = out_str.Npunc;
    vNshrt = out_str.vNshrt;   
    vNpunc = out_str.vNpunc;  
    vNrepInt = out_str.vNrepInt;
    vNrepRem = out_str.vNrepRem; 
	idxCwLen = out_str.idxCwLen;
	idxRate = out_str.idxRate;
    K0 = out_str.K0;
	
	vector<vector<double> > G_parity;
	parityMatrixGen(idxCwLen,idxRate,G_parity);
	//校验矩阵大小
	int M,N;
	int Mset[3][4] = {
		{324,216,162,108},
		{648,432,324,216},
		{972,648,486,324},
	};
	int Nset[3][4] = {
		{324,432,486,540},
		{648,864,972,1080},
		{972,1296,1458,1620},
	};
	M = Mset[idxCwLen-1][idxRate-1];
	N = Nset[idxCwLen-1][idxRate-1];
	int qIn =0,qOut =0;//position of the input and output bits
	int cwBg,cwEnd;
	if(cwIdx!=0)
	{
		cwBg = cwIdx;  
		cwEnd = cwIdx;	
		Nsym = 1;
	}
	else
	{
		cwBg = 1;   
		cwEnd = Ncw;
	}

	int *pktEncOut;
	pktEncOut = new int [Nsym * out_str.Ncbps];
	
	int k =cwBg-1;
	while(k<cwEnd)
	{
		//insert shorten bits
		//int vNshrtnum;
		//vNshrtnum = (int *)vNshrt[k];
		int Ninfo = K0-vNshrt[k];
		int *xIn;
		xIn = new int[Ninfo+vNshrt[k]];
		for(int i=0;i<Ninfo;i++)
			xIn[i] = bitIn[qIn+i];
		for(int j=Ninfo;j<Ninfo+vNshrt[k];j++)
			xIn[j] = 0;

		int *xInParity;
	    xInParity = new int [M];
	    for (int i=0;i<M;i++)
			xInParity[i] = 0;
		for (int i=0;i<M;i++)
		{
			for (int j=0;j<N;j++)
				xInParity[i] = xInParity[i]+G_parity[i][j]*xIn[j];//矩阵乘法
			xInParity[i] = xInParity[i] % 2;
		}//ldpc encode

		if( Npunc > 0)			//puncture
		{
			int *xOut;
			xOut = new int [Ninfo+M-vNpunc[k]];
			for (int i=0;i<Ninfo;i++)
				xOut[i] = bitIn[qIn+i];
			for(int j=Ninfo;j<Ninfo+M-vNpunc[k];j++)
				xOut[j] = xInParity[j-Ninfo];
			for (int i=0;i<Ninfo+M-vNpunc[k];i++)
				 pktEncOut[qOut+i] = xOut[i];
			qOut = qOut+Ninfo+M-vNpunc[k];
			delete [] xOut;
		}
		else
		{
			int *xOutShort;
			xOutShort = new int[Ninfo+M];
			for (int i=0;i<Ninfo;i++)
				xOutShort[i] = bitIn[qIn+i];
			for(int j=Ninfo;j<Ninfo+M;j++)
				xOutShort[j] = xInParity[j-Ninfo];
			if(vNrepInt[k])
			{
				int*xOutRepInt;
				xOutRepInt = new int[3*(Ninfo+M)];
				for(int i=0;i<3;i++)
				{
					for(int j=0;j<Ninfo+M;j++)
						xOutRepInt[i*(Ninfo+M)+j] = xOutShort[j];
				}
				int *xOut;
			    xOut = new int [4*(Ninfo+M)+vNrepRem[k]];
				for (int i=0;i<Ninfo+M;i++)
					xOut[i] = xOutShort[i];
				for (int j=Ninfo+M;j<4*(Ninfo+M);j++)
					xOut[j] = xOutRepInt[j];
				for (int r=3*(Ninfo+M);r<4*(Ninfo+M)+vNrepRem[k];r++)
					xOut[r] = xOutShort[r-3*(Ninfo+M)];
				for (int i=0;i<4*(Ninfo+M)+vNrepRem[k];i++)
					pktEncOut[qOut+i] = xOut[i];
				qOut = qOut+4*(Ninfo+M)+vNrepRem[k];

				delete [] xOutRepInt;
				delete [] xOut;
			}
			else
			{
				int *xOut;
			    xOut = new int [(Ninfo+M)+vNrepRem[k]];
				for (int i=0;i<Ninfo+M;i++)
					xOut[i] = xOutShort[i];
				for (int j=Ninfo+M;j<(Ninfo+M)+vNrepRem[k];j++)
					xOut[j] = xOutShort[j-(Ninfo+M)];
				for (int i=0;i<(Ninfo+M)+vNrepRem[k];i++)
					pktEncOut[qOut+i] = xOut[i];
				qOut = qOut+(Ninfo+M)+vNrepRem[k];
				delete [] xOut;
			}
			delete [] xOutShort;
			delete [] xInParity;
		}
		qIn = qIn + Ninfo;
		k++;		
	}
	if((qOut != out_str.Ncbps * Nsym || qOut != out_str.Navbits))
		std::cout << "LDPC PPDU encoder output length is not equal to Ncbps*Nsym";

	applyLdpcEnc_out Sout;
	Sout.pktEncOut.resize(out_str.Ncbps * Nsym);
	for(int i=0;i<out_str.Ncbps * Nsym;i++)
		Sout.pktEncOut[i] = pktEncOut[i];
	Sout.n_sym = Nsym;
	return Sout;
}