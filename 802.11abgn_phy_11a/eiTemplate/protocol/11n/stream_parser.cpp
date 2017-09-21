#include"StdAfx.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<vector>

using namespace std;

int **stream_parser(vector<vector<int>> bitenc_penc,vector<int> n_bpscs,int n_ss,int n_es)
{
//-------------------------------------------------------------------------------//
//  Function Discription: stream parser
//-------------------------------------------------------------------------------//
//  History:
//    Created by Li Yinan    Date:2014-11-10    Version:1.0
//-------------------------------------------------------------------------------//
//  Fuction List
//-------------------------------------------------------------------------------//
//  Input Parameters:
//    bitenc_penc[]: encoded bits per encoder
//    n_bpscs[]: number of bits per subcarrier
//    n_ss: number of spatial streams
//    len1: length of bitenc_pen
//    len2: length of n_bpscs
//-------------------------------------------------------------------------------//
//  Output Parameters:
//    **bit_pss: output of stream_parser
//-------------------------------------------------------------------------------//
//  Reference: stream_parser.m
//-------------------------------------------------------------------------------//
//  Note:
//    len1 must be divisible by s_cap
//    s_cap can be seen in the function
//-------------------------------------------------------------------------------//
	int n_bitpenc,n_totbit,s_cap=0,n_scap,i_enc,i_ss,sum_1=0,i,j,a,b,m=0,x=0,y=0;
	int *s_low,*sum;
	int **bit_pss;

	n_bitpenc = bitenc_penc[0].size();
	n_totbit = n_es * n_bitpenc;
	a = 1;
	b = n_bpscs.size();

	int count=0;
	for(i=0;i<b;i++)
	{
		if(n_bpscs[i]!=0)
			count++;
	}

	s_low = (int *)malloc(count*sizeof(int));
	for(j = 0; j < count; j++)
	{
		s_low[j] = n_bpscs[j]/2;
		if (s_low[j] < 1)
			s_low[j] = 1;
		s_cap = s_cap + s_low[j];
	}//max,sum

	if (n_totbit%s_cap != 0)
	{
		cout<<"Indivisible number of bits";
	}
	        
	n_scap = floor(double(n_bitpenc/s_cap));

	vector<vector<int>> bitenc_ss(s_cap,vector<int>(n_es*n_scap));

	for(i_enc = 0; i_enc < n_es; i_enc++)
	{
		for(j = 0; j < n_es*n_scap; j=j+n_es)
		{
			for(i = 0; i < s_cap; i++)
			{
				bitenc_ss[i][j] = bitenc_penc[i_enc][m*s_cap+i];
			}
			m++;
			if(m == n_scap)
				break;
		}//assign valus of bitenc_ss
	}
	if(n_bitpenc%s_cap!=0)
	{
		vector<int> temp(n_es*(n_bitpenc-n_scap*s_cap));
		for(i=0;i<n_es;i++)
			for(j=0;j<n_bitpenc-n_scap*s_cap;j++)
				temp[i*(n_bitpenc-n_scap*s_cap)+j] = bitenc_penc[i][j+n_scap*s_cap];
		vector<vector<int>> temp1(s_cap,vector<int>(temp.size()/s_cap));
		for(i=0;i<s_cap;i++)
			for(j=0;j<temp.size()/s_cap;j++)
				temp1[i][j]=temp[j*s_cap+i];
		bitenc_ss.resize(s_cap,vector<int>(n_es*n_scap+temp.size()/s_cap));
		for(i=0;i<s_cap;i++)
			for(j=0;j<(int)temp1[0].size();j++)
				bitenc_ss[i][n_es*n_scap+j] = temp1[i][j];
	}

	bit_pss = (int **)malloc(n_ss*sizeof(int *));
	for(i_ss = 0; i_ss < n_ss; i_ss++)
	{
		bit_pss[i_ss] = (int *)malloc(s_low[i_ss]*n_es*n_scap*sizeof(int));
		i = 0;
		sum_1 = 0;
		sum = (int *)malloc(s_low[i_ss]*sizeof(int));
		while(i < i_ss)
		{
			sum_1 = sum_1 + s_low[i];
			i++;
		}
		for(i = 0; i < s_low[i_ss]; i++)
		{
			sum[i] = sum_1 + i;
		}
		j = 0;
		for(y = 0; y < n_es*n_scap; y++)
		{
			for(i = 0; i < s_low[i_ss]; i++)
			{
				bit_pss[i_ss][j+i] = bitenc_ss[sum[i]][y];//bitenc_ss[3][0]meiyou 
			}
			j=j+s_low[i_ss];
		}
		free(sum);//assign valus of bit_pss
	}

	free(s_low);
	//release related pointer

return(bit_pss);
}