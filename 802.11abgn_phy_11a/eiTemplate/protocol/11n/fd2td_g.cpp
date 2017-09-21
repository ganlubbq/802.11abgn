//----------------------------------------------------//
// Function Description:802.11n transmit simulation
//       Frequency domain to time domain conversion
//    IDFT and time windowing, supporting up to 160MHz
//----------------------------------------------------//
// History:
// Created by Liyuli   Date:2014-11-11    Version:1.0
//
//----------------------------------------------------//
// Function List:
//----------------------------------------------------//
// Input Parameters:
//       df:输入数据
// gi_short:
//   params:结构体
//----------------------------------------------------//
// Output Parameters:
//      dto:
//----------------------------------------------------//
// Reference:
//----------------------------------------------------//
// Note:
#include "stdafx.h"
#include<iostream>
#include<complex>
#include<vector>
#include<cmath>
//#include<mat.h>
#include"ifft.h"
#include"primaryFunctionalFunc.h"

using namespace std;

vv_c_dl fd2td_g(complex<double> **df,bool gi_short,paramsFather params)
{
	int i,j;
	unsigned int NFFT = params.BSS_NFFT;
	int N_tx = params.N_tx;
	int nr = N_tx;
	int nf = NFFT;
	int WIN_len = params.WINDOW.size();
	//zeros padding and shift 
	vv_c_dl ftemp(nr,vector<complex<double> >(NFFT)); //nr*NFFT数组，初始化为0
	if(nf != NFFT)    //nf must be smaller than NFFT
	{
		for(i = 0;i < nr;i++)    //给ftemp赋值
		{
			for(j = 0;(unsigned int)j < NFFT;j++)
			{
				if(j<nf/2)
					ftemp[i][j] = df[i][nf/2+j];
				else if((unsigned int)j >= (NFFT-nf/2))
					ftemp[i][j] = df[i][j-NFFT+nf/2];  
			}
		}
	}
	else
	{
		for(i = 0;i < nr;i++)
			for(j = 0;(unsigned int)j < NFFT;j++)
				ftemp[i][j] = df[i][(j + NFFT/2) % NFFT];
	}

	vv_c_dl dt(nr,vector<complex<double> >(NFFT));
	
	for(i = 0;(unsigned int)i < ftemp.size();i++)
	{
		dt[i] = ifft(ftemp[i]);
	}
	for(i = 0;(unsigned int)i < dt.size();i++)
		for(j = 0;(unsigned int)j < dt[0].size();j++)
			dt[i][j]=dt[i][j]*(double)NFFT;


	int cp_len;
	if(gi_short)
	{
		cp_len = NFFT/8;
	}
	else
	{
		cp_len = NFFT/4;
	}

	int symb_len = NFFT + cp_len;

	vv_c_dl dt_cp(dt.size(),vector<complex<double> >(symb_len));
	for(i = 0;(unsigned int)i < dt.size();i++)
	{
		for(j=0;j<symb_len;j++)
		{
			if(j<cp_len)
			{
				dt_cp[i][j]=dt[i][j+NFFT-cp_len];
			}
			else
			{
				dt_cp[i][j]=dt[i][j-cp_len];
			}
		}
	}
	int w_col,dta_col;
	switch(params.App_Win)
	{
		case 2:
			w_col=WIN_len;dta_col=dt_cp[0].size()+2*NFFT;
			break;
		case 1:
			w_col=symb_len+1;dta_col=w_col;
			break;
		case 0:
			w_col=symb_len;dta_col=0;
			break;
	}

	vector<vector<double> > w(N_tx,vector<double>(w_col));;
	vv_c_dl dta(dt_cp.size(),vector<complex<double> >(dta_col));
	vv_c_dl dto(dt_cp.size(),vector<complex<double> >(w_col));
	
	double tneg;
	switch(params.App_Win){
	case 2:                                 //测试没问题
		{//dta赋值
			for(i = 0;(unsigned int)i < dt_cp.size();i++)
			{
				for(j = 0;(unsigned int)j < (dt_cp[0].size()+2*NFFT);j++)
				{
					if((unsigned int)j < NFFT)
						dta[i][j]=dt_cp[i][j];
					else if((unsigned int)j < NFFT+dt_cp[0].size())
						dta[i][j]=dt_cp[i][j-NFFT];
					else
						dta[i][j]=dt_cp[i][j-2*NFFT];
				}
			}
			//w赋值
			for(i=0;i<N_tx;i++)
			{
				for(j=0;j<WIN_len;j++)
					w[i][j]=params.WINDOW[j];
			}
			tneg = params.WTINDEX[0];

		    //dto赋值
			for(i = 0;(unsigned int)i < dta.size();i++)
			{
				for(j = 0;(unsigned int)j < WIN_len;j++)
					dto[i][j]=dta[i][j+NFFT+tneg] * w[i][j];   
			}
			break;
		}

	case 1:
	
		{//w赋值未写  w = ones(N_tx, 1) * filter(params.WINDOWF, 1, [ones(1, symb_len) zeros(1, 1)]);
			double *filter = new double[symb_len+1];
			for(i=0;i<symb_len+1;i++)
				filter[i]=1;
			filter[0]=params.WINDOWF[0];
			filter[symb_len]=params.WINDOWF[1];
			//double **w = new double *[N_tx];
			for(i=0;i<N_tx;i++)
				for(j=0;j<symb_len+1;j++)
					w[i][j] = filter[j];

			//dta赋值
			for(i = 0;(unsigned int)i < dt_cp.size();i++)
			{
				for(j = 0;(unsigned int)j < w[0].size();j++)
				{
					if((unsigned int)j < dt_cp[0].size())
						dta[i][j]=dt_cp[i][j];	
					else
						dta[i][j]=dt_cp[i][j-NFFT];
				}
			}
			//dto赋值
			for(i = 0;(unsigned int)i < dta.size();i++)
				for(j = 0;(unsigned int)j < symb_len+1;j++)
					dto[i][j]=dta[i][j] * w[i][j];
			delete [] filter;
			break;
		}
	case 0:
		{
			for(i=0;(unsigned int)i < dt_cp.size();i++)
				for(j=0;(unsigned int)j < symb_len;j++)
					dto[i][j]=dt_cp[i][j];
			break;
		}
	default:
		cout<<"Input parameters error!"<<endl;
	}
	return dto;
}