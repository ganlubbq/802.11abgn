#include "stdafx.h"
#include<iostream>
#include<vector>
#include"primaryFunctionalFunc.h"

using namespace std;

static short scram_state = 0;
static short bscram(short bit_in)
{
	short retv;	
    #define Bit3xBit6 (((scram_state >> 3) ^ (scram_state >> 6)) & 1)
	retv = (bit_in ^ Bit3xBit6) & 1;
	scram_state = ((scram_state << 1) | Bit3xBit6) & 0x7F;
	return retv;
}

double* scram_t(short *in,int size)
{	
	if(size > 655350L) 
	{
	  cout<<"The input vector is too long."<<endl;
	  goto Usage;
	}

	double* temp=new double[size];

	if(size != -1) 
	{
		scram_state = (short) size;
	}

	for(int i = 0; i < size; i++)
	{
		temp[i] = (double) bscram((short) in[i]);
	}

	return temp;	
	
Usage:
	cout<<"Usage: [out] = scram(count, in).\nIf count == -1, the scrambler state is not initialised."<<endl;
	return temp;
}

vector<vector<int> >  pilot_map(vector<int> n, int start_seq, int modtype,int N_sts,int i_sts)
{
//----------------------------------------------------//
// Function Description:802.11n transmit simulation
//                  Function to generate pilot symbols
//----------------------------------------------------//
// History:
// Created by Liyuli   Date:2014-11-4    Version:1.0
//
//----------------------------------------------------//
// Function List:
//----------------------------------------------------//
// Input Parameters:
//        n:indices of symbols
//start_seq:starting point in pseudo-random polarity 
//             sequence [for n = 0]
//  modtype:1 [20 MHz legacy], 2 [20 MHz HT], 3 [40 MHz HT]
//    N_sts:
//    i_sts:
//----------------------------------------------------//
// Output Parameters:
//        omap:
//----------------------------------------------------//
// Reference:
//----------------------------------------------------//
// Note:
	int i,j;
	int NFFT = (1+(modtype == 3))*64;

	short bit[127];	
	for(i=0;i<127;i++)
	{
		bit[i]=1;
	}
	double* out = NULL;
	out = scram_t(bit,127);
	double pilot_polarity[127];
	for(i=0;i<127;i++)
	{
		pilot_polarity[i] = 2 * out[i] - 1;
	}


	int pilot_schemes1[6] = {1,0,1,1,1,-1};
	int pilot_pos1[4] = {-21,-7,7,21};

	int pilot_schemes2[10][6] = {1, 0,  1,  1,  1, -1,
		2, 0,  1,  1, -1, -1, 
		2, 1,  1, -1, -1,  1, 
		3, 0,  1,  1, -1, -1,
		3, 1,  1, -1,  1, -1,
		3, 2, -1,  1,  1, -1,
		4, 0,  1,  1,  1, -1,
		4, 1,  1,  1, -1,  1, 
		4, 2,  1, -1,  1,  1, 
		4, 3, -1,  1,  1,  1
	};
	int pilot_pos2[4] = {-21,-7,7,21};

	int pilot_schemes3[10][8] = {1, 0,  1,  1,  1, -1, -1,  1, 
		2, 0,  1,  1, -1, -1, -1, -1, 
		2, 1,  1,  1,  1, -1,  1,  1, 
		3, 0,  1,  1, -1, -1, -1, -1, 
		3, 1,  1,  1,  1, -1,  1,  1, 
		3, 2,  1, -1,  1, -1, -1,  1, 
		4, 0,  1,  1, -1, -1, -1, -1, 
		4, 1,  1,  1,  1, -1,  1,  1, 
		4, 2,  1, -1,  1, -1, -1,  1, 
		4, 3, -1,  1,  1,  1, -1,  1 
	};
	int pilot_pos3[6] = {-53, -25, -11, 11, 25, 53};

	vector<vector<int> >pilot_schemes;
	vector<int>pilot_pos;

	switch(modtype)
	{
	case 1://20 MHz legacy, IEEE802.11a-1999, p. 31, eq. (24)
		pilot_schemes.resize(1);
		pilot_schemes[0].resize(6);
		for(i=0;i<1;i++)
		{
			for(j=0;j<6;j++)
			{
				pilot_schemes[i][j] = pilot_schemes1[j];
			}
		}
		pilot_pos.resize(4);
		for(i=0;i<4;i++)
		{
			pilot_pos[i] = pilot_pos1[i];
		}
		break;

	case 2://% 20 MHz HT
		pilot_schemes.resize(10);
		pilot_schemes[0].resize(6);
		for(i=0;i<10;i++)
		{
			for(j=0;j<6;j++)
			{
				pilot_schemes[i][j] = pilot_schemes2[i][j];
			}
		}
		pilot_pos.resize(4);
		for(i=0;i<4;i++)
		{
			pilot_pos[i] = pilot_pos2[i];
		}
		break;

	case 3://40 MHz HT, IEEE802.11n-D1.0, p. 209, table n767
		pilot_schemes.resize(10);
		pilot_schemes[0].resize(8);
		for(i=0;i<10;i++)
		{
			for(j=0;j<8;j++)
			{
				pilot_schemes[i][j] = pilot_schemes3[i][j];
			}
		}
		pilot_pos.resize(6);
		for(i=0;i<6;i++)
		{
			pilot_pos[i] = pilot_pos3[i];
		}
		break;
	}

	vector<int> pilots(pilot_schemes[0].size()-2);
	for(i=0;i<pilot_schemes.size();i++)
	{
		if((pilot_schemes[i][0] == N_sts) && (pilot_schemes[i][1] == i_sts))
		{
			for(j=0;j<pilot_schemes[0].size()-2;j++)
			{
				pilots[j]=pilot_schemes[i][j+2];
			}
		}
	}

	vector<vector<int> > pilot_m(pilots.size(),vector<int>(n.size()));
	for(int i=0;i<pilots.size();i++)
	{
		for(j=0;j<n.size();j++)
		{
			pilot_m[i][j] =  pilots[i] * pilot_polarity[(start_seq + n[j])%127];
		}
	}
	//Rotate pilot patterns
	//VERIFYTHIS, hopefully against standard sample
	int p1=pilot_pos.size();

	if(modtype > 1)
	{
		vector<vector<int> > pilot_mtp(pilots.size(),vector<int>(n.size()));
		for(i=0;i<pilot_m.size();i++)
		{
			for(j=0;j<n.size();j++)
			{
				pilot_mtp[i][j]=pilot_m[(i+n[j])%p1][j];
			}
		}
		pilot_m.swap(pilot_mtp);
	}
	
	//Map pilots to subcarriers
	vector<vector<int> > pilot_f(NFFT,vector<int>(n.size()));
	for(i=0;i<p1;i++)
	{
		for(j=0;j<pilot_m[0].size();j++)
		{
			pilot_f[pilot_pos[i]+NFFT/2][j] = pilot_m[i][j];
		}
	}

	return pilot_f;
}

