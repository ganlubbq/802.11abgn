//---------------------------------------------------------------------------------------------------------//
	//	Function Description: segment_parser
	//---------------------------------------------------------------------------------------------------------//
	//	History:
	//		Created by LiuHang			Date: 2014-11-4			Version: 1.0
	//
	//---------------------------------------------------------------------------------------------------------//
	//	Function List:
	//---------------------------------------------------------------------------------------------------------//
	//	Input Parameters:
	//			n_cbpss :
	//			s:
	//			n_es : 
	//---------------------------------------------------------------------------------------------------------//
	//	Output Parameters:
	//			*p_idx_o : segment parser index
	//---------------------------------------------------------------------------------------------------------//
	// Reference:
	//		segment_parser.m
	//---------------------------------------------------------------------------------------------------------//
	
#include <iostream>
#include <vector>
#include"primaryFunctionalFunc.h"
#include "stdafx.h"

using namespace std;

vector<int> segment_parser(int n_cbpss, int s, int n_es)
{
	
	vector<int> p_idx_o;
	int s_blk = s * n_es;

	int nint_blk = n_cbpss / (2 * s_blk);

	vector<vector<int>   >   idx_tmp1(s_blk,   vector<int>(nint_blk * 2));

	int k = 1;
	for (int j = 0; j < nint_blk * 2; j++)
	{
		for (int i = 0; i < s_blk; i++)
		{
			idx_tmp1[i][j] = k;
			k++;
		}
	}

	vector<vector<int> > idx_o_tmp1(s_blk*nint_blk, vector<int>(2));
	k = 0;
	for (int i = 0; i < s_blk; i++)
	{
		for (int j = 0; j<nint_blk * 2; j = j + 2)
		{
			idx_o_tmp1[k][0] = idx_tmp1[i][j];
			idx_o_tmp1[k][1] = idx_tmp1[i][j+1];
			k++;
		}
	}

	if(n_cbpss%(2*s_blk) != 0)
	{
		vector <vector<int> > idx_tmp2(s,vector<int>( (n_cbpss - nint_blk * 2 * s_blk) / s) );

		k = nint_blk * 2 * s_blk + 1;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < (n_cbpss - nint_blk * 2 * s_blk) / s; j++)
			{
				idx_tmp2[i][j] = k;
				k++;
			}
		}

		vector<vector<int> > idx_o_re( (n_cbpss - nint_blk * 2 * s_blk) / 2 ,vector<int>(2));
		k = 0;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < (n_cbpss - nint_blk * 2 * s_blk) / s; j = j + 2)
			{
				idx_o_re[k][0] = idx_tmp2[i][j];
				idx_o_re[k][1] = idx_tmp2[i][j + 1];
				k++;
			}
		}

		vector<vector<int> > idx_o_tmp2(n_cbpss/2, vector<int>(2));
		k = 0;
		for (int i = 0; i < s_blk*nint_blk; i++)
		{
			idx_o_tmp2[k][0] = idx_o_tmp1[i][0];
			idx_o_tmp2[k][1] = idx_o_tmp1[i][1];
			k++;
		}
		for (int i = 0; i < (n_cbpss - nint_blk * 2 * s_blk) / 2; i++)
		{
			idx_o_tmp2[k][0] = idx_o_re[i][0];
			idx_o_tmp2[k][1] = idx_o_re[i][1];
			k++;
		}

		k = 0;
		vector<int> idx_o(n_cbpss);
		for (int i = 0; i < n_cbpss/2; i++)
		{
			idx_o[k] = idx_o_tmp2[i][0];
			k++;
		}
		for (int i = 0; i < n_cbpss/2; i++)
		{
			idx_o[k] = idx_o_tmp2[i][1];
			k++;
		}
		p_idx_o.resize(idx_o.size());
		for( int i = 0; i < n_cbpss; i++)
		{
			p_idx_o[i] = idx_o[i];
		}
	}
	else
	{
		k = 0;
		vector<int> idx_o(s_blk*nint_blk * 2);
		for (int i = 0; i < s_blk*nint_blk; i++)
		{
			idx_o[k] = idx_o_tmp1[i][0];
			k++;
		}

		for (int i = 0; i < s_blk*nint_blk; i++)
		{
			idx_o[k] = idx_o_tmp1[i][1];
			k++;
		}
		p_idx_o.resize(idx_o.size());
		for( int i = 0; i < s_blk*nint_blk*2; i++)
		{
			p_idx_o[i] = idx_o[i];
		}
	}
	return p_idx_o;
}
//²âÊÔÓÃ´úÂë
/*
int main()
{
	int n_cbpss = 468 * 2;
	int s = 1;
	int n_es =1;
	int s_blk = s * n_es;
	int nint_blk = n_cbpss / (2 * s_blk);
	int len = 0;
	if(n_cbpss%(2*s_blk) != 0)
	{
		len = n_cbpss;
	}
	else
	{
		len = s_blk * nint_blk * 2;
	}
	int *p_idx_o = new int[len];
	segment_parser(n_cbpss, s, n_es, p_idx_o);
	for(int i = 0; i < len; i++)
	{
		cout<<p_idx_o[i]<<endl;
	}
	system("pause");
	return 0;
}
*/