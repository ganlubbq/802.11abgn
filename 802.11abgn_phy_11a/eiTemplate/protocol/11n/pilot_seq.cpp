//---------------------------------------------------------------//
//  Function Description:   Pilot sequence generation
//---------------------------------------------------------------//
// History:
//    Created by Wubing  Data:2014-11-8 Version:1.0
//    Modified by hxy    Data:2014-12-14 Version:2.0
//---------------------------------------------------------------//
// Function List:
//---------------------------------------------------------------//
//Input Paraneters:
//        idx_sym:index of the ofdm symbol
//        n:idx_sym的长度
//        polar_ofset:index of polarisation offset
//        mode:E_VHT, E_HT_GF, E_HT_MF, E_NON_HT, E_NON_HT_DUP
//        N_sts:number of STS
// Output Paraneters:
//        s_pilot_f: 产生的pilot序列
//--------------------------------------------------------------//
//#include<iostream>
#include "stdafx.h"
#include<stdlib.h>
#include<math.h>
#include "primaryFunctionalFunc.h"

int **pilot_seq(int idx_sym,int polar_ofset,int mode,int N_sts,paramsFather params,wlan_consts consts)
{
	int n_20=params.N_20M;
	int n_pilot=params.Indx_pilot.size();
	int **s_pilot_f;
	
	//导频的下标
	int *Idx_pilot=(int *)malloc(n_pilot*sizeof(int));
	for(int i=0;i<n_pilot;i++)
	{
		Idx_pilot[i]=params.Indx_pilot[i];
	}
	int Index_tem=consts.Polar_pilot[(idx_sym+polar_ofset)%127];//完成固定参数的计算
	switch(mode)
	{
	case 3://E_VHT:
		{
			s_pilot_f=new int*[1];
			if(n_20<8)
			{
				int *s_pilot_bs=(int *)malloc(n_pilot*sizeof(int));
			    int *idx_cycrep=(int *)malloc(n_pilot*sizeof(int));
				s_pilot_f[0]=(int *)malloc(n_pilot*sizeof(int));
				for(int i=0;i<n_pilot;i++)
				{
					s_pilot_bs[i]=consts.S_pilot_80[i];
					idx_cycrep[i]=(i+idx_sym)%n_pilot;
				}
				for(int i=0;i<n_pilot;i++)
					s_pilot_f[0][i]=s_pilot_bs[idx_cycrep[i]]*Index_tem;
				free(s_pilot_bs);
				free(idx_cycrep);
			}
			else
			{
				int *s_pilot_bs=(int *)malloc(8*sizeof(int));
			    int *idx_cycrep=(int *)malloc(8*sizeof(int));
				s_pilot_f[0]=(int *)malloc(16*sizeof(int));
				for(int i=0;i<8;i++)
				{
					s_pilot_bs[i]=consts.S_pilot_80[i];
					idx_cycrep[i]=(i+idx_sym)%8;
				}
				for(int i=0;i<8;i++)
				{
					s_pilot_f[0][i]=s_pilot_bs[idx_cycrep[i]]*Index_tem;
					s_pilot_f[0][i+8]=s_pilot_bs[idx_cycrep[i]]*Index_tem;
				}
				free(s_pilot_bs);
				free(idx_cycrep);
			}
			break;
		}
	case 2://E_HT_GF:
	case 1://E_HT_MF:
		{
			//s_pilot_f[N_sts][N_pilot]
			s_pilot_f=(int **)malloc(N_sts*sizeof(int));//二维矩阵
			//标准协议中有表格定义
			switch(n_20)
			{
			case 1:
				{
					n_pilot=4;
				    int *idx_cycrep=(int *)malloc(n_pilot*sizeof(int));
			        for(int i=0;i<N_sts;i++)
						s_pilot_f[i]=(int *)malloc(n_pilot*sizeof(int));
					for(int i=0;i<n_pilot;i++)
						idx_cycrep[i]=(i+idx_sym)%n_pilot+1;
					switch(N_sts)
					{
					case 1:
						{
							int s_pilot_bs[1][4]={1,1,1,-1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					case 2:
						{
							int s_pilot_bs[2][4]={1,1,-1,-1,1,-1,-1,1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					case 3:
						{
							int s_pilot_bs[3][4]={1,1,-1,-1,1,-1,-1,1,-1,1,1,-1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					case 4:
						{
							int s_pilot_bs[4][4]={1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					}
					free(idx_cycrep);
					break;
				}
			case 2:
				{
					n_pilot=6;
					int *idx_cycrep=(int *)malloc(n_pilot*sizeof(int));
					for(int i=0;i<N_sts;i++)
						s_pilot_f[i]=(int *)malloc(n_pilot*sizeof(int));
					for(int i=0;i<n_pilot;i++)
						idx_cycrep[i]=(i+idx_sym)%n_pilot+1;
					switch(N_sts)
					{
					case 1:
						{
							int s_pilot_bs[1][6]={1,1,1,-1,-1,1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					case 2:
						{
							int s_pilot_bs[2][6]={1,1,-1,-1,-1,-1,1,1,1,-1,1,1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					case 3:
						{
							int s_pilot_bs[3][6]={1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1};
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						} 
					case 4:
						{
							int s_pilot_bs[4][6]={1,1,-1,-1,-1,-1,1,1,1,-1,1,1,1,-1,1,-1,-1,1,-1,1,1,1,-1,1};   
							for(int i=0;i<n_pilot;i++)
								for(int j=0;j<N_sts;j++)
									s_pilot_f[j][i]=s_pilot_bs[j][idx_cycrep[i]-1]*Index_tem;
							break;
						}
					}
					free(idx_cycrep);
					break;
				}
			}
			break;
		}
	case 0://E_NON_HT:
	case 10://E_NON_HT_DUP:
	case 4://E_UNDET:
		{
			int s_pilot[4]={1,1,1,-1};
			s_pilot_f = new int*[1];
			s_pilot_f[0] = new int [4];
			for(int i=0;i<4;i++)
				s_pilot_f[0][i]=s_pilot[i]*Index_tem;
			break;
		}
	}
	return s_pilot_f;
}