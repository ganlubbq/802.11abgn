#ifndef LDPC_ENCODE_H_
#define LDPC_ENCODE_H_

#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <cstdarg>
#include "wlan_txparam.h"

struct File_Index
{
	int idxCwLen;
	int idxRate;
};

struct applyLdpcEnc_out
{
	vector<int> pktEncOut;
	int n_sym;
};

ldpcPara ldpc_encpara_g(int bit_len,MCSMode fec_str,int m_stbc);
void parityMatrixGen(int length, int rate,vector<vector<double> > &G_parity);
#endif