/*----------------------------------------------------
 Function Description: BCC encoder wrapper
---------------------------------------------------
History:
Created by hxy   Date:2014-12-4    Version:1.0
----------------------------------------------------
Function List:
---------------------------------------------------
 Input Parameters:
        byte_in    : information byte input
		length     : Length of byte_in
        fec_str    : FEC structure
         .n_dbps   : number of total data bits
         .n_cbps   : number of total encoded bits
         .crate    : code rate
         .n_es     : number of codeblocks
        scram_seed : scrambler seed
		crc_sigb   : crc of sigb
----------------------------------------------------
Output Parameters:
        bit_o : coded bits
		N_sym  : 
---------------------------------------------------*/
//注：不输出tv_bcc
#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <string.h>
#include "transform_bits_num.h"
#include "scramble.h"
#include "wlan_txparam.h"

using namespace std;
//enc_str  某种结构体类型
int* conve(int *bit_in,long BitLength,bool ts);

vector<vector<int>> bcc_encoder(int *byte_in, int L,int length,MCSMode enc_str, int scram_seed, int &N_sym, int crc_sigb,int source_len)
{
	int N_es = enc_str.nes_a;
	/*int N_ttailb = 6*N_es;
	int N_dbps = enc_str.ndbps;
	int N_bin = 8*length;
	int N_pad = N_sym*N_dbps - (N_bin+16+N_ttailb);
	int *scr_seed = &scram_seed;*/
	int *crcsigb = &crc_sigb;
	/*bit_info = new int[N_bin];	
	bit_info = num2bitsv(byte_in,length,8);*/
	int M;
	int **bitscr_pblk;
	double rate = enc_str.raten;
	//tv_bcc.bit_info = bit_info;

	//the parsing operation
	if (enc_str.enc_type == 1)
	{
		bitscr_pblk = new int *[N_es];
		M =   L/N_es+6;
		for(int i=0;i<N_es;i++)
			bitscr_pblk[i] = new int [M];

		for(int i=0;i<N_es;i++)
		{
			for(int j=0;j<L/N_es;j++)
				bitscr_pblk[i][j] = byte_in[N_es*j+i];
			for(int j=L/N_es;j<M;j++)
				bitscr_pblk[i][j] = 0;
		}
	}
	else
	{
		M = L/N_es;
		bitscr_pblk = new int *[N_es]; //可能分两个流
		for(int i=0;i<N_es;i++)
			bitscr_pblk[i] = new int [M];
		for(int i=0;i<N_es;i++){
			for(int j=0;j<M;j++)
				bitscr_pblk[i][j] = byte_in[N_es*j+i];
			for(int j=source_len;j<source_len+6;j++)
				bitscr_pblk[i][j] = 0;
		}
			
	}

	//分流卷积
	int **bitenc_pblk;
	bitenc_pblk = new int *[N_es];
	for(int i=0;i<N_es;i++)
		bitenc_pblk[i] = new int [2*M];
	//卷积函数和matlab比对正确
	int count = 0;
	while(count!=N_es)
	{
		bitenc_pblk[count] = conve(bitscr_pblk[count],M,1);
		count++;
	}
	//need to move the reference to code rate outside the function
	//char *rate1="1/2",*rate2="2/3",*rate3="3/4",*rate4="5/6";
	//打孔
	int bit_len = M/rate;
	vector<vector<int>> bit_o(N_es,vector<int>(bit_len));
	if(rate==0.5)//rate = 1/2
	{
		for(int i=0;i<N_es;i++)
			for(int j=0;j<bit_len;j++)
				bit_o[i][j] = bitenc_pblk[i][j];
	}
	else if(rate==(double)2/3)//rate = 2/3
	{
		for(int i=0;i<N_es;i++)
			for(int j=0;j<M;j++)
			{
				if (j%2==0)
				{
					bit_o[i][j*3/2]=bitenc_pblk[i][j*2];
				    bit_o[i][j*3/2+1]=bitenc_pblk[i][j*2+1];
				}
				else
				{
					bit_o[i][(j-1)*3/2+2]=bitenc_pblk[i][j*2];
				}
			}
	}
	else if(rate==(double)3/4)//rate = 3/4
	{
		for(int i=0;i<N_es;i++)
			for(int j=0;j<M;j++)
			{
				if (j%3==0)
				{
					bit_o[i][j*4/3]=bitenc_pblk[i][j*2];
				    bit_o[i][j*4/3+1]=bitenc_pblk[i][j*2+1];
				}
				else if(j%3==1)
				{
					bit_o[i][(j-1)*4/3+2]=bitenc_pblk[i][j*2];
				}
				else
				{
					bit_o[i][(j-2)*4/3+3]=bitenc_pblk[i][j*2+1];
				}
			}
	}
	else if(rate==(double)5/6)//rate = 5/6
	{
		for(int i=0;i<N_es;i++)
			for(int j=0;j<M;j++)
			{
				if (j%5==0)
				{
					bit_o[i][j*6/5]=bitenc_pblk[i][j*2];
					bit_o[i][j*6/5+1]=bitenc_pblk[i][j*2+1];
				}
				else if(j%5==1)
				{
					bit_o[i][(j-1)*6/5+2]=bitenc_pblk[i][j*2];
				}
				else if(j%5==2)
				{
					bit_o[i][(j-2)*6/5+3]=bitenc_pblk[i][j*2+1];
				}
				else if(j%5==3)
				{
					bit_o[i][(j-3)*6/5+4]=bitenc_pblk[i][j*2];
				}
				else
				{
					bit_o[i][(j-4)*6/5+5]=bitenc_pblk[i][j*2+1];
				}
			}
	}
	else
		cout << "Unknown code rate!";
	return bit_o;
}
