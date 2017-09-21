#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include"transform_bits_num.h"
#include"primaryFunctionalFunc.h"


using namespace std;

complex<double> *qam_map256(int *b_in,int N_bpsc,int b_n)
{   
	std::complex<double> QPSK_D[4];
	QPSK_D[0]=std::complex<double>(-0.7071, -0.7071);  QPSK_D[1]=std::complex<double>(-0.7071, 0.7071);
	QPSK_D[2]=std::complex<double>(+0.7071, -0.7071);  QPSK_D[3]=std::complex<double>(+0.7071, 0.7071);
	int b_n1=b_n;//±£¡Ù≥§∂»
	b_n=b_n/N_bpsc;
	int* symbs=(int *)malloc(b_n*sizeof(int));
	symbs=bits2numv(b_in,b_n1,N_bpsc);
	double * ibits=(double *)malloc(b_n*sizeof(double));
	double* qbits=(double *)malloc(b_n*sizeof(double));
	double cmul;
	int *w;

	complex<double> *map;
	map=new complex<double> [b_n];

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
	case 8:
		{
			cmul=1/sqrt(170.0);
			int v[16]={-15,-13,-9,-11,-1,-3,-7,-5,15,13,9,11,1,3,7,5};
			w=v;
			for(int i=0;i<b_n;i++)
		    {
				ibits[i]=floor((double)symbs[i]/16);
				qbits[i] = symbs[i]&15;
		    }
			break;
		}
	default:
		puts("N_bpsc is wrong");
	}
	double I,Q;
	for(int i=0;i<b_n;i++)
	{
		if(N_bpsc==1)
			map[i]=complex<double>(w[(int)(ibits[i])]*cmul);
		else{
			I = int(w[(int)ibits[i]]*cmul*10000);
			Q = int(w[(int)qbits[i]]*cmul*10000);
			map[i]=complex<double>(I/10000.0,Q/10000.0);
		}
			
	}
	return map;
}
	