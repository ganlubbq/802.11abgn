//----------------------------------------------------//
// Function Description:802.11n transmit simulation
//  Cyclic shift [delay] in frequency domain, by n samples
//----------------------------------------------------//
// History:
// Created by Liyuli   Date:2014-11-11    Version:1.0
// Modified by hxy     Date:2014-12-15    Version:2.0
//----------------------------------------------------//
// Function List:
//----------------------------------------------------//
// Input Parameters:
//       vi:matrix with freq domain N_sts or N_tx lines of length NFFT
//        n:column vector of delays
//     NFFT:
//----------------------------------------------------//
// Output Parameters:
//        vo:
//----------------------------------------------------//
// Reference:
//----------------------------------------------------//
// Note:
#include "stdafx.h"
#include<iostream>
#include<complex>
#include<cmath>
#include"primaryFunctionalFunc.h"

using namespace std;
complex<double> **fcycdel_g(complex<double> **vi,int row,int colum,double *n,int NFFT)
{
	int nr = row;
	int nvi = colum;
	complex<double> **vitemp = new complex<double>*[nr];
	for(int i=0;i<nr;i++)
		vitemp[i] = new complex<double> [NFFT];
	for(int i=0;i<nr;i++)
		for(int j=0;j<NFFT;j++)
			vitemp[i][j]=0;
	for(int i=0;i<nr;i++)
	{
		for(int j=(NFFT/2-nvi/2);j<(NFFT/2+nvi/2);j++)
		{
			vitemp[i][j]=vi[i][j-NFFT/2+nvi/2];
		}
	}
	
	int *vk = new int[NFFT];
	for(int i=0;i<NFFT;i++)
	{
		vk[i] = i - NFFT/2; 
	}

	complex<double> **vo = new complex<double>*[nr];
	for(int i=0;i<nr;i++)
		vo[i] = new complex<double> [NFFT];
	complex<double> **nvktemp = new complex<double>*[nr];
	for(int i=0;i<nr;i++)
		nvktemp[i] = new complex<double> [NFFT];

	//æÿ’Û≥À∑®
	for(int i=0;i<row;i++)
		for(int j=0;j<NFFT;j++)
			nvktemp[i][j]=n[i]*vk[j];
	
	complex<double> a(0,-1);

	for(int i=0;i<nr;i++)
		for(int j=0;j<NFFT;j++)
			vo[i][j]=vitemp[i][j]*exp(a*2.0*pi_*nvktemp[i][j]/(double)NFFT);

	return vo;
}