#pragma once

//基本的功能性函数声明
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <complex>
#include <cmath>
#include <vector>
#include "transform_bits_num.h"
#include "wlan_txparam.h"
#include "wlan_const_set.h"

using namespace std;

typedef vector<vector<complex<double> > > vv_c_dl; //double复数二维数组
typedef vector<vector<vector<complex<double>>>> Vec_compA_3D;//double复数3维数组
#define pi_ 3.1415926535898

void bitrev(int *in, int len, int N, int *out);
int* crc32(int *in,int L);
int crc8(vector<int> in);
int *cshifts(int N,int htpart);
complex<double> **fcycdel_g(complex<double> **vi,int row,int colum,double *n,int NFFT);
vv_c_dl fd2td_g(complex<double> **df,bool gi_short,paramsFather params);
//int *interleave_ac(int *symb,int i_ss,int N_bpsc,int modtype,int N_ss);
int* interleave_n(int* dataIn, int modType, int format, int MCS, int BW, int iss, int Nbpscs);
int **pilot_seq(int idx_sym,int polar_ofset,int mode,int N_sts,paramsFather params,wlan_consts consts);
double scale(int format,wlan_txparam txvector,int n_20);
vector<vector<int> >  pilot_map(vector<int> n, int start_seq, int modtype,int N_sts,int i_sts);
complex<double> *qam_map(int *b_in,int N_bpsc,int b_n,int modtype);
complex<double> *qam_map256(int *b_in,int N_bpsc,int b_n);
vector<int> segment_parser(int n_cbpss, int s, int n_es);
void mcs_tbl_ac(int bw_typ, int n_ss, int *p_mcs_typ_row, int **p_mcs_tbl );
int* conve(int *bit_in,long BitLength,bool ts);
Vec_compA_3D txSymbolAssembly(Vec_compA_3D preamble,Vec_compA_3D data,wlan_txparam txvector);