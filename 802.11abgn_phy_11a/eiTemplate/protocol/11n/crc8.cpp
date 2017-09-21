#include<iostream>
#include<vector>
#include"primaryFunctionalFunc.h"
#include "stdafx.h"

using namespace std;
int crc8(vector<int> in)
{
//----------------------------------------------------//
// Function Description:802.11n transmit simulation
//	                    CRC-8 used in HT-SIG
//----------------------------------------------------//
// History:
// Created by Liyuli   Date:2014-10-28    Version:1.0
//
//----------------------------------------------------//
// Function List:
//----------------------------------------------------//
// Input Parameters:
//           in:输入0,1比特序列
//----------------------------------------------------//
// Output Parameters:
//           ou:
//----------------------------------------------------//
// Reference:
//----------------------------------------------------//
// Note:
	int poly=7;
	int m = 255;
	vector<int> a(in);
	int get_8bit=0x000000ff;

	for(int k=1;k<=a.size();k++)
	{
		int b=((m/128)^a[k-1])&get_8bit;
		m=((m<<1)^(poly*b))&get_8bit;
	}

	int ou = (m^255)&get_8bit;
	return ou;
}
/*void main()
{
	int ar[]={1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1};
	int size = sizeof(ar)/sizeof(ar[0]);
	vector<int> vec(ar,ar+size);
	cout<<crc8(vec)<<endl;	
	
}*/
