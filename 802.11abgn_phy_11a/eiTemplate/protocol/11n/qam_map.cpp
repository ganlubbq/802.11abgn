//----------------------------------------------------//
// Function Description: 802.11n transmit simulation
//----------------------------------------------------//
// History:
//     Created: Wubing Data:2014-11-8 Version:1.0
//
//---------------------------------------------------//
// Function List;
//---------------------------------------------------//
// Input Parameters:
//          b_in:输入序列
//          N_bpsc:QAM类型
//          b_n:输入序列的长度
//---------------------------------------------------//
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<complex>
#include"transform_bits_num.h"
#include "primaryFunctionalFunc.h"

using namespace std;

std::complex<double> *qam_map(int *b_in,int N_bpsc,int b_n,int modtype)
{

	int b_n1=b_n;//保留长度
	b_n=b_n/N_bpsc;
	int* symbs=(int *)malloc(b_n*sizeof(int));
	symbs=bits2numv(b_in,b_n1,N_bpsc);
	double * ibits=(double *)malloc(b_n*sizeof(double));
	double* qbits=(double *)malloc(b_n*sizeof(double));
	double cmul;
	int *w;

	complex<double> *map;
	map=new complex<double> [b_n];
	
	complex<double> *s_qam;
	s_qam=new complex<double> [b_n];

	switch(N_bpsc)
	{
	case 1://BPSK
		{
			cmul=1.0;
			int v[2]={-1,1};
			w=v;
			for(int i=0;i<b_n;i++)
			{
				ibits[i]=symbs[i];
				qbits[i]=0;
			}
			break;
		}
	case 2://QPSK
		{
			cmul=1/sqrt(2.0);
			int v[2]={-1,1};
			w=v;
			for(int i=0;i<b_n;i++)
			{
				ibits[i]=floor((double)symbs[i]/2);
				qbits[i] = symbs[i]&1;
			}
			break;
		}
		
	case 4://16QAM
		{
			cmul=1/sqrt(10.0);
			int v[4]={-3,-1,3,1};
			w=v;
		    for(int i=0;i<b_n;i++)
			{
				ibits[i]=floor((double)symbs[i]/4);
				qbits[i] = symbs[i]&3;
			}
			break;
		}
	
	case 6://64QAM
		{
			cmul=1/sqrt(42.0);
		    int v[8]={-7,-5,-1,-3,7,5,1,3};
		    w=v;
		    for(int i=0;i<b_n;i++)
		    {
				ibits[i]=floor((double)symbs[i]/8);
				qbits[i] = symbs[i]&7;
		    }
		   break;
		}
	default:
		puts("N_bpsc is wrong");
	}
	for(int i=0;i<b_n;i++)
	{
		if(N_bpsc==1)
			map[i]=(complex<double>)(w[(int)(ibits[i])]*cmul);
		else
			map[i]=(complex<double>)(w[(int)(ibits[i])]*cmul,w[(int)qbits[i]]*cmul);
	}
	
    int NFFT=(1+(modtype==3))*64;
	complex<double> *omap;
	omap=new complex<double> [NFFT];

	for(int i=0;i<NFFT;i++)
		omap[i]=0.0;
	switch(modtype)
	{
		case 1:// Legacy 20M [802.11a-1999, p. 31, eq (23)]
			{
				int M_k[48]={-26,-25,-24,-23,-22,-20,-19,-18,
					-17,-16,-15,-14,-13,-12,-11,-10,-9,-8,-6,
					-5,-4,-3,-2,-1,1,2,3,4,5,6,8,9,10,11,12,
					13,14,15,16,17,18,19,20,22,23,24,25,26};
				for(int i=0;i<48;i++)
					omap[M_k[i]+NFFT/2]=map[i];				
				break;
			}
		case 2://HT 20M,    [802.11n-D1.0, p. 212, eq (20-52)]
			{
				int M_k[52]={-28,-27,-26,-25,-24,-23,-22,-20,
					-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,
					-9,-8,-6,-5,-4,-3,-2,-1,1,2,3,4,5,6,8,9,
					10,11,12,13,14,15,16,17,18,19,20,22,23,24,25,26,27,28};
				for(int i=0;i<52;i++)
					omap[M_k[i]+NFFT/2]=map[i];
				break;
			}
		case 3://HT 40M,    [802.11n-D1.0, p. 213, eq (20-54)]
			{
				int M_k[108]={-58,-57,-56,-55,-54,-52,-51,-50,
					-49,-48,-47,-46,-45,-44,-43,-42,-41,-40,-39,
					-38,-37,-36,-35,-34,-33,-32,-31,-30,-29,-28,
					-27,-26,-24,-23,-22,-21,-20,-19,-18,-17,-16,
					-15,-14,-13,-12,-10,-9,-8,-7,-6,-5,-4,-3,-2,
					2,3,4,5,6,7,8,9,10,12,13,14,15,16,17,18,19,
					20,21,22,23,24,26,27,28,29,30,31,32,33,34,
					35,36,37,38,39,40,41,42,43,44,45,46,47,48,
					49,50,51,52,54,55,56,57,58};
				for(int i=0;i<108;i++)
					omap[M_k[i]+NFFT/2]=map[i];
				break;
			}
		default:puts("N_bpsc is wrong");
	}
	return omap;


}
