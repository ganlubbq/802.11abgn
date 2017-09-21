/*----------------------------------------------------
 Function Description: LDPC encoder wrapper
---------------------------------------------------
History:
Created by hxy   Date:2014-12-1    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
        bit_len     : information byte input
        fec_str     : FEC structure
          .n_dbps   : number of total data bits
          .n_cbps   : number of total encoded bits
          .crate    : code rate
          .n_es     : number of codeblocks
          .scr_seed : scrambler seed
        m_stbc      : number of STBC
----------------------------------------------------
Output Parameters:
           ldpcPara : LAPC parameters
---------------------------------------------------*/
#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "ldpc_encode.h"
#include "wlan_txparam.h"

int Lldpc=0, Ncw=0;
File_Index FileIdx={0,0};
void getEncPara(int Navbits,int Npld,double rate,int & Lldpc,int &Ncw,File_Index & FileIdx);
int round(double a);


ldpcPara ldpc_encpara_g(int bit_len,MCSMode fec_str,int m_stbc)
{
	int Ndbps,Ncbps,Nsym,Npld,Navbits,K0,Nshrt,Nspcw,Npunc;
	double rate;
	int *vNshrt;
	int *vNpunc;
	int *vNrepInt;
	int *vNrepRem;
	int *vCwLen;
	int tem;double tem1;
	//ldpcPara out_str; 
	rate  = fec_str.raten;
    Ndbps  = fec_str.ndbps;
    Ncbps  = fec_str.ncbps;

	//a) Compute the number of available bits
	Npld = bit_len + 16;
	tem1 = (double)Npld / (Ndbps * m_stbc);
    Navbits = Ncbps * m_stbc * ceil(tem1);

	//b) Compute the integer number of LDPC codewords to be transmitted
	getEncPara(Navbits, Npld, rate,Lldpc,Ncw,FileIdx);
	K0 = Lldpc * rate;

	//c) Compute nubmer of shortening bits
	tem = Ncw * Lldpc * rate - Npld;
    Nshrt = 0>tem?0:tem;       
	vNshrt = new int(Ncw);
	int Nsp1;
	if(Nshrt > 0)
	{
		Nspcw = Nshrt / Ncw;
		Nsp1 = Nshrt % Ncw;
		for(int i=0;i<Nsp1;i++)
			vNshrt[i] = Nspcw+1;
		for(int j=Nsp1;j<Ncw;j++)
			vNshrt[j] = Nspcw;
	}
	vCwLen = new int(Ncw);
	for(int i=0;i<Ncw;i++)
		vCwLen[i] =Lldpc - vNshrt[i];		

	//d) Compute bit to be punctured
	double temA,temB,temC;
	tem = (Ncw * Lldpc) - Navbits - Nshrt;
    Npunc = 0>tem?0:tem;
	temA = 0.1 * Ncw * Lldpc * (1-rate);
    temB = 1.2 * Npunc * (rate /(1-rate));
    temC = 0.3 * Ncw * Lldpc *(1-rate);
	if( ( (Npunc > temA) && (Nshrt < temB)) || (Npunc > temC))
	{
		Navbits = Navbits + Ncbps * m_stbc;
        tem = (Ncw * Lldpc) - Navbits - Nshrt;
        Npunc = 0>tem?0:tem;
	}
	int Nppcw = Npunc / Ncw;
	vNpunc = new int(Ncw);
	Nsym = Navbits / Ncbps;
	if (Npunc > 0)
    {
		int Npp1 = Npunc % Ncw;  // discard parity bits: (n-k-Nppcw-1 : n-k-1)
        for(int i=0;i<Npp1;i++)
			vNpunc[i] = Nppcw+1;
		for(int j=Nsp1;j<Ncw;j++)
			vNpunc[j] = Nppcw;// discard parity bits: (n-k-Nppcw : n-k-1)
		for(int i=0;i<Ncw;i++)
			vCwLen[i] = vCwLen[i] - vNpunc[i];
	}

	//e) Compute number of coded bits to be repeated, valid only when Npunc==0
	double tem2 = Navbits - (Ncw * Lldpc * (1-rate)) - Npld;
    int Nrep = 0>round(tem2)?0:round(tem2);
	vNrepInt = new int(Ncw);
	vNrepRem = new int(Ncw);
	for(int i=0;i<Ncw;i++)
	{
		vNrepInt[i]=0;
		vNrepRem[i]=0;
	}
	if( Npunc == 0 && Nrep > 0)
	{
		int repBit = Nrep / Ncw;
		int Np1 = Nrep % Ncw;
		for(int i=0;i<Np1;i++)
		{
			vNrepInt[i] = (repBit+1)/vCwLen[i];
			vNrepRem[i] = repBit+1-vNrepInt[i]*vCwLen[i];
		}
		for(int j=Np1;j<Ncw;j++)
		{
			vNrepInt[j] = repBit/vCwLen[j];
			vNrepRem[j] = repBit-vNrepInt[j]*vCwLen[j];
		}
		for(int i=0;i<Np1;i++)
			vCwLen[i] = vCwLen[i]+repBit+1;
		for(int j=Np1;j<Ncw;j++)
			vCwLen[j] = vCwLen[j]+repBit;
	}
	ldpcPara out_str;
	out_str.Lldpc = Lldpc;        
	out_str.Ncw = Ncw; 
	out_str.Nsym = Nsym;
	out_str.Ncbps = Ncbps;
    out_str.Navbits = Navbits;    
	out_str.K0 = K0;
    out_str.rate = rate;

    out_str.Nshrt = Nshrt;        
	out_str.Npunc = Npunc;
    out_str.Nrep = Nrep;

    // the following vectors are 1-by-Ncw
    out_str.vNshrt = vNshrt;  // Nspcw for each codeword:
    out_str.vNpunc = vNpunc;     // Nppcw for each codeword
    out_str.vNrepInt = vNrepInt; // repeat number of the whole codeword
    out_str.vNrepRem = vNrepRem; // repeat number of bits in a codeword

    out_str.vCwLen = vCwLen;   // codeword length after discard shorten bits, punc or repeat

    out_str.idxCwLen = FileIdx.idxCwLen;
	out_str.idxRate = FileIdx.idxRate;
	
	//delete [] vNshrt;
	//delete [] vCwLen;
	//delete [] vNpunc;
	//delete [] vNrepInt;
	//delete [] vNrepRem;
	return out_str;
}
	
void getEncPara(int Navbits,int Npld,double rate,int & Lldpc,int &Ncw,File_Index & FileIdx)
// Table20-15: PPDU encoding parameters
// Lldpc: LDPC codeworklength
// Ncw: number of LDPC codewords
// FileIdx: index of generating matrix
//    FileIdx.idxCwLen: index of codeword length: [648, 1296, 1944] => [1, 2, 3]
//    FileIdx.idxRate: index of rate: [1/2, 2/3, 3/4, 5/6] => [1, 2, 3, 4]
// Npld: number of bits int ehPSDU and SERVICE field
{
	int rateScale;
	double tem;
	if(Navbits <= 648)
	{
		Ncw = 1;
		tem = Npld+912*(1-rate);
		if(Navbits >= tem)
			Lldpc = 1296;
		else
			Lldpc = 648;
	}
	else if( Navbits <= 1296)
	{
		Ncw =1;
	    tem = Npld+1464*(1-rate);
		if(Navbits >= tem)
			Lldpc = 1944;
		else
		    Lldpc = 1296;
	}
	else if( Navbits <= 1944 )
	{
		Ncw =1;
		Lldpc = 1944;
	}
	else if( Navbits <= 2592)
	{
		Ncw = 2;
        tem = Npld + 2916*(1-rate);
        if( Navbits >= tem)
			Lldpc = 1944;
        else
			Lldpc = 1296;
	}
	else
	{
		Ncw = ceil((float)Npld / (1944 * rate));
		Lldpc = 1944;
	}

	switch( Lldpc)
	{
	case 648:
		{
			FileIdx.idxCwLen = 1;
			break;
		}
	case 1296:
		{
			FileIdx.idxCwLen = 2;
			break;
		}
	case 1944:
		{
			FileIdx.idxCwLen = 3;
			break;
		}
	default:
		std::cout << "unknown codeword length" << std::endl;
	}

	rateScale = rate*12;
	switch(rateScale)
	{
	case 6:
		{
			FileIdx.idxRate = 1;
			break;
		}
	case 8:
		{
			FileIdx.idxRate = 2;
			break;
		}
	case 9:
		{
			FileIdx.idxRate = 3;
			break;
		}
	case 10:
		{
			FileIdx.idxRate = 4;
			break;
		}
	default:
		std::cout << "unknown code rate" << std::endl;
	}
}

int round(double a)
{
	int temp,out;
	temp = floor(a);
	if(a-temp<0.5)
		out =temp;
	else
		out = ceil(a);
	return out;
}