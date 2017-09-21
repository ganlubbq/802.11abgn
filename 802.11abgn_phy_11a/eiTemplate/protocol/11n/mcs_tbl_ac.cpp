//---------------------------------------------------------------------------------------------------------//
	//	Function Description: mcs_tbl_ac
	//---------------------------------------------------------------------------------------------------------//
	//	History:
	//		Created by LiuHang			Date: 2014-11-1			Version: 1.0
	//
	//---------------------------------------------------------------------------------------------------------//
	//	Function List:
	//---------------------------------------------------------------------------------------------------------//
	//	Input Parameters:
	//			bw_typ :bandwidth 带宽 值为1,4-8
	//			             E_LEG20M=1
	//			             E_VHT20M=4
	//			             E_VHT40M=5
	//			             E_VHT80M=6
	//			             E_VHT160M=7
	//			             E_VHT80P80M=8
	//			n_ss    : number of spatial streams 值1-4
	//			bw_typ取1时，n_ss只能取1
	//			*p_mcs_typ_row : mcs table row number			
	//---------------------------------------------------------------------------------------------------------//
	//	Output Parameters:
	//			**p_mcs_tbl ：mcs table
	//---------------------------------------------------------------------------------------------------------//
	// Reference:
	//		mcs_tbl_ac.m
	//---------------------------------------------------------------------------------------------------------//

#include <iostream>
#include <vector>
#include <cmath>
#include "primaryFunctionalFunc.h"
#include "stdafx.h"
//#include "constants_def.h"
using namespace std;

void mcs_tbl_ac(int bw_typ, int n_ss, int *p_mcs_typ_row, int **p_mcs_tbl )
{

	const double max_blksize = 2160;

	//HT mcs>=8
	int mcs_type_n[8][3] = {{1, 1, 2}, 
	                          {2, 1, 2},
	                          {2, 3, 4},
	                          {4, 1, 2},
	                          {4, 3, 4},
	                          {6, 2, 3},
	                          {6, 3, 4},
	                          {6, 5, 6}};

	//和不同速率的mcs匹配，用于确定调制方式和码率
	//mcs 0-7
	int mcs_type_a[8][3] = {{1, 1, 2},
		                    {1, 3, 4},
							{2, 1, 2},
							{2, 3, 4},
							{4, 1, 2},
							{4, 3, 4},
							{6, 2, 3},
							{6, 3, 4}};

	int N_sd = 0;
	int *p_mcs_type = NULL;

	switch (bw_typ)  //带宽类型
	{
	case 0://E_LEG20M 和11a类似
			N_sd = 48;
			n_ss = 1;
			p_mcs_type = &mcs_type_a[0][0];
			*p_mcs_typ_row = 8;
			break;
	case 1://E_HT20M:
			N_sd = 52;
			p_mcs_type = &mcs_type_n[0][0];
			*p_mcs_typ_row = 8;
			break;
	case 2://E_HT40M :
			N_sd = 108;
			p_mcs_type = &mcs_type_n[0][0];
			*p_mcs_typ_row = 8;
			break;
	//case 5://E_VHT80M :
	//		N_sd = 234; 
	//		p_mcs_type = &mcs_type_ac[0][0];
	//		*p_mcs_typ_row = 10;
	//		break;
	//case 6://E_VHT160M :
	//		N_sd = 468; 
	//		p_mcs_type = &mcs_type_ac[0][0];
	//		*p_mcs_typ_row = 10;
	//		break;
	//case 7://E_VHT80P80M:
	//		N_sd = 468;
	//		p_mcs_type = &mcs_type_ac[0][0];
	//		*p_mcs_typ_row = 10;
	//		break;
	}
	
	  //vector<vector<int>>   mcs_tbl(*p_mcs_typ_row,vector<int>(8));
	  int** mcs_tbl = p_mcs_tbl;

	  for (int i = 0; i < *p_mcs_typ_row; i++)
	  {
		  mcs_tbl[i][1] = N_sd;          //数据子载波的个数
		  mcs_tbl[i][5] = *(p_mcs_type + i * 3 + 1);
		  mcs_tbl[i][6] = *(p_mcs_type + i * 3 + 2);
		  mcs_tbl[i][7] = 1;
	  }

	  for (int i_mcs = 0; i_mcs < *p_mcs_typ_row; i_mcs++)
	  {
		  mcs_tbl[i_mcs][0] = *(p_mcs_type + i_mcs * 3 );//每个载波编码比特数
		  mcs_tbl[i_mcs][2] = N_sd * mcs_tbl[i_mcs][0] * n_ss;//每个符号编码比特数
		  mcs_tbl[i_mcs][3] = mcs_tbl[i_mcs][2] * (*(p_mcs_type + i_mcs * 3 + 1)) 
												/ (*(p_mcs_type + i_mcs * 3 + 2));//每个符号未编码比特数
		  int N_es = ceil(mcs_tbl[i_mcs][3] / max_blksize);
		  mcs_tbl[i_mcs][4] = N_es;
		  if (mcs_tbl[i_mcs][3]%N_es != 0 || mcs_tbl[i_mcs][2]% N_es != 0)
		  {
			  mcs_tbl[i_mcs][7] = 0;
		  }
	  }

	  
	  //switch(bw_typ)
	  //{
	  //case 3://E_VHT20M:
		 // if(n_ss!=3&&n_ss!=6)
			//  for (int j = 0; j < 8; j++)
			//	  p_mcs_tbl[9][j] = 0;
		 // break;
	  //case 5://E_VHT80M:
		 // if (n_ss==3||n_ss==7)
			//  for (int j = 0; j < 8; j++)
			//	  p_mcs_tbl[6][j] = 0;
		 // else if (n_ss==6)
			//  for (int j = 0; j < 8; j++)
			//	  p_mcs_tbl[9][j] = 0;
		 // break;
	  //case 6://E_VHT160M:
	  //case 7://E_VHT80P80M:
		 // if (n_ss==3)
			//  for (int j = 0; j < 8; j++)
			//	  p_mcs_tbl[9][j] = 0;
		 // break;
	  //default:
		 // break;
	  //}
}

