#ifndef WLAN_CONST_SET_H_
#define WLAN_CONST_SET_H_

#include <complex>
#include "scramble.h"
#include <iostream>

using namespace std;

struct wlan_consts
{
	//BW refers to the bandwidth occupied by a single signal replica
	int BW_per_bw_type[8];
	string ModtypeNames[8];

	int Num_BW_seg[8];
	int BW_per_bw_seg[8];
	int Nsd_per_seg[8];
	int Nst_per_seg[8];

	int N_sd_per_modtype[8];
	int Max_Streams_per_modtype[8];
	int N_tones_per_modtype[8];

	//20M, 40M, 80M, 160M
	int bw_code[4][2];
	//STF
	complex<double> L_STF_20[53];
	//LTF
	int NLTF_tble[8];
	int LTF_L[26];
	int LTF_R[26];
	int L_LTF_20[53];

	int P_4x4[4][4];
	complex<double> P_6x6[6][6];
	complex<double> P_8x8[8][8];

	double Pi_4x4[4][4];
	complex<double> Pi_6x6[6][6];
	complex<double> Pi_8x8[8][8];

	int R_4x4[4];
	complex<double> R_6x6[6];
	complex<double> R_8x8[8];

	double Ri_4x4[4][4];
	complex<double> Ri_6x6[6][6];
	complex<double> Ri_8x8[8][8];

	//cyclic delay values
	int cshifts_vht[8][8];

	//pilot and pilot subcarrier locations
	int S_pilot_20[4];
	int S_pilot_40[6];
	int S_pilot_80[8];

	int Idx_pilot_20[4];
	int Idx_pilot_40[6];
	int Idx_pilot_80[8];
	int Idx_pilot_160[16];

	int Polar_pilot[127];

	//Following data subcarrier locations
	int idx_dsubc_20leg[48];
	int idx_dsubc_20[52];
	int idx_dsubc_40[108];
	int idx_dsubc_80[234];
	int idx_dsubc_160[468];

	//per 20MHz phase rotation
    int Gamma_20;
    complex <double> Gamma_40[2][1];
    int Gamma_80[4][1];
    int Gamma_160[8][1];

	//interleave parameters
	//columns   : legacy 20M, HT 20M, HT 40M, HT 80M
    //first row : number of columns
    //second row: times of Nbpscs
    //third row : number of rotations
	int intlv_param[4][4];

	int rate_table[8][4];

	//tone mapping distance for 20M, 40M, 80M, 160/80+80M                    
    int tonemapping_table[4];
};

wlan_consts wlan_constsValue(wlan_consts consts);
#endif