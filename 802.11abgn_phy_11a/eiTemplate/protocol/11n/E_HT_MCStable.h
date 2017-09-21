#ifndef E_HT_MCSTABLE_H_
#define E_HT_MCSTABLE_H_

#include <cstring>
#include <vector>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

struct MCSpara
{
	vector<int> mcs;
	vector<vector<int>> mods;
	vector<string> crate;
	vector<double> raten;
	vector<vector<int>> nes;
	vector<int> ndbps;
};

const int mod20[77][4]={{1,0,0,0},{2,0,0,0},{2,0,0,0},{4,0,0,0},{4,0,0,0},
		{6,0,0,0},{6,0,0,0},{6,0,0,0},{1,1,0,0},{2,2,0,0},{2,2,0,0},{4,4,
		0,0},{4,4,0,0},{6,6,0,0},{6,6,0,0},{6,6,0,0},{1,1,1,0},{2,2,2,0},
		{2,2,2,0},{4,4,4,0},{4,4,4,0},{6,6,6,0},{6,6,6,0},{6,6,6,0},{1,1,
		1,1},{2,2,2,2},{2,2,2,2},{4,4,4,4},{4,4,4,4},{6,6,6,6},{6,6,6,6},
		{6,6,6,6},{0,0,0,0},{4,2,0,0},{6,2,0,0},{6,4,0,0},{4,2,0,0},{6,2,
		0,0},{6,4,0,0},{4,2,2,0},{4,4,2,0},{6,2,2,0},{6,4,2,0},{6,4,4,0},
		{6,6,2,0},{6,6,4,0},{4,2,2,0},{4,4,2,0},{6,2,2,0},{6,4,2,0},{6,4,
		4,0},{6,6,2,0},{6,6,4,0},{4,2,2,2},{4,4,2,2},{4,4,4,2},{6,2,2,2},
		{6,4,2,2},{6,4,4,2},{6,4,4,4},{6,6,2,2},{6,6,4,2},{6,6,4,4},{6,6,
		6,2},{6,6,6,4},{4,2,2,2},{4,4,2,2},{4,4,4,2},{6,2,2,2},{6,4,2,2},
		{6,4,4,2},{6,4,4,4},{6,6,2,2},{6,6,4,2},{6,6,4,4},{6,6,6,2},{6,6,6,4}};
const string crate20[77]={"1/2","1/2","3/4","1/2","3/4","2/3","3/4","5/6",//0-7
	"1/2","1/2","3/4","1/2","3/4","2/3","3/4","5/6",//8-15
	"1/2","1/2","3/4","1/2","3/4","2/3","3/4","5/6",//16-23
	"1/2","1/2","3/4","1/2","3/4","2/3","3/4","5/6",//24-31
	"0",
	"1/2","1/2","1/2","3/4","3/4","3/4",//33-38
	"1/2","1/2","1/2","1/2","1/2","1/2","1/2",//39-45
	"3/4","3/4","3/4","3/4","3/4","3/4","3/4",//46-52
	"1/2","1/2","1/2","1/2","1/2","1/2","1/2","1/2","1/2","1/2","1/2","1/2",//53-64
	"3/4","3/4","3/4","3/4","3/4","3/4","3/4","3/4","3/4","3/4","3/4","3/4"};//65-76
const double raten20[77]={0.5,0.5,0.75,0.5,0.75,2.0/3,0.75,5.0/6,
	0.5,0.5,0.75,0.5,0.75,2.0/3,0.75,5.0/6,
	0.5,0.5,0.75,0.5,0.75,2.0/3,0.75,5.0/6,
	0.5,0.5,0.75,0.5,0.75,2.0/3,0.75,5.0/6,
	0,0.5,0.5,0.5,0.75,0.75,0.75,
	0.5,0.5,0.5,0.5,0.5,0.5,0.5,
	0.75,0.75,0.75,0.75,0.75,0.75,0.75,
	0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,
	0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75,0.75};
const int ndbps20[77]={26,52,78,104,156,208,234,260,52,104,
	156,208,312,416,468,520,78,156,234,312,
	468,624,702,780,104,208,312,416,624,832,
	936,1040,0,156,208,260,234,312,390,208,
	260,260,312,364,364,416,312,390,390,468,
	546,546,624,260,312,364,312,364,416,468,
	416,468,520,520,572,390,468,546,468,546,
	624,702,624,702,780,780,858};
const int ndbps40[77]={54,108,162,216,324,432,486,540,
	108,216,324,432,648,864,972,1080,
	162,324,486,648,972,1296,1458,1620,
	216,432,648,864,1296,1728,1944,2160,
	24,324,432,540,486,648,810,432,540,540,
	648,756,756,864,648,810,810,972,1134,1134,
	1296,540,648,756,648,756,864,972,864,972,
	1080,1080,1188,810,972,1134,972,1134,1296,
	1458,1296,1458,1620,1620,1782};


//构建mcs表 mcs=0-76
void HT_MCSvalue(vector<MCSpara> &mcs20,vector<MCSpara> &mcs40)
{
		//20M 0-31是必选方式，33-76是可选方式
		mcs20.resize(1);
		mcs20[0].mcs.resize(77);
		mcs20[0].mods.resize(77,vector<int>(4));
		mcs20[0].crate.resize(77);
		mcs20[0].raten.resize(77);
		mcs20[0].nes.resize(77,vector<int>(2));
		mcs20[0].ndbps.resize(77);               
		for (int iter=0;iter<77;iter++)
		{
			mcs20[0].mcs[iter] = iter;
			for(int i=0;i!=4;i++)
				mcs20[0].mods[iter][i] = mod20[iter][i];//每种mcs下每个流的调制方式
			mcs20[0].crate[iter] = crate20[iter];//??
			mcs20[0].raten[iter] = raten20[iter];
			mcs20[0].nes[iter][0]=mcs20[0].nes[iter][1]=1;
			mcs20[0].ndbps[iter] = ndbps20[iter];
		}
		//40M 0-31是必选方式，MCS32，33-76是可选方式
		mcs40.resize(1);
		mcs40[0].mcs.resize(77);
		mcs40[0].mods.resize(77,vector<int>(4));
		mcs40[0].crate.resize(77);
		mcs40[0].raten.resize(77);
		mcs40[0].nes.resize(77,vector<int>(2));
		mcs40[0].ndbps.resize(77);
		for (int iter=0;iter<77;iter++)
		{
			mcs40[0].mcs[iter] = iter;
			for(int i=0;i!=4;i++)
				mcs40[0].mods[iter][i] = mod20[iter][i];
			mcs40[0].crate[iter] = crate20[iter];
			mcs40[0].raten[iter] = raten20[iter];
			mcs40[0].nes[iter][0]=mcs40[0].nes[iter][1]=1;
			mcs40[0].ndbps[iter] = ndbps40[iter];
		}
		//mcs==32 特殊情况单独赋值
		mcs40[0].mods[32][0]=1;
		mcs40[0].crate[32] = "1/2";
		mcs40[0].raten[32] = 0.5;
		mcs40[0].nes[21][0]=mcs40[0].nes[21][1]=2;
		mcs40[0].nes[22][0]=mcs40[0].nes[22][1]=2;
		mcs40[0].nes[23][0]=mcs40[0].nes[23][1]=2;
		for(int i=0;i<4;i++)
			mcs40[0].nes[28+i][0]=mcs40[0].nes[28+i][1]=2;
		mcs40[0].nes[50][1]=2;
		mcs40[0].nes[51][1]=2;
		mcs40[0].nes[52][0]=mcs40[0].nes[52][1]=2;
		mcs40[0].nes[64][1]=2;
		mcs40[0].nes[67][1]=2;
		mcs40[0].nes[69][1]=2;
		for(int i=0;i<7;i++)
			mcs40[0].nes[69+i][0]=mcs40[0].nes[69+i][1]=2;
}
#endif